#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

class VisionFirstTrentPlacer {
private:
    int N, ti, tj;
    vector<unsigned char> blocked, observed, visited;

    const int di4[4]  = {-1, 1, 0, 0};
    const int dj4[4]  = {0, 0, -1, 1};

    int total_open_cells = 0;

    // Tarjan
    vector<int> disc, low, parent;
    vector<unsigned char> is_art;
    int timer = 0;
    bool goal_reached = false;
    int reachable_count = 0;

    inline int idx(int i, int j) const { return i * N + j; }
    inline bool inBounds(int i, int j) const { return 0 <= i && i < N && 0 <= j && j < N; }

    inline bool hasAdjacentT(int i, int j) const {
        for (int d=0; d<4; ++d) {
            int ni=i+di4[d], nj=j+dj4[d];
            if (inBounds(ni,nj) && blocked[idx(ni,nj)]) return true;
        }
        return false;
    }

    void dfsArt(int u) {
        disc[u] = low[u] = ++timer;
        int ui=u/N, uj=u%N;
        int child=0;
        ++reachable_count;
        if (u == idx(ti,tj)) goal_reached = true;

        for (int d=0; d<4; ++d) {
            int vi=ui+di4[d], vj=uj+dj4[d];
            if (!inBounds(vi,vj)) continue;
            int v=idx(vi,vj);
            if (blocked[v]) continue;

            if (disc[v]==-1) {
                parent[v]=u; ++child; dfsArt(v);
                low[u]=min(low[u], low[v]);
                if (parent[u]!=-1 && low[v] >= disc[u]) is_art[u]=1;
            } else if (v != parent[u]) {
                low[u]=min(low[u], disc[v]);
            }
        }
        if (parent[u]==-1 && child>1) is_art[u]=1;
    }

    bool recomputeArticulation() {
        fill(disc.begin(), disc.end(), -1);
        fill(low.begin(),  low.end(),  0);
        fill(parent.begin(), parent.end(), -1);
        fill(is_art.begin(), is_art.end(), 0);
        timer=0; goal_reached=false; reachable_count=0;

        int si=0, sj=N/2, s=idx(si,sj);
        if (blocked[s]) return false;
        dfsArt(s);
        return goal_reached && (reachable_count == total_open_cells);
    }

    inline bool canPlaceByArt(int i,int j,bool ignore_adjacent_T) const {
        if (!inBounds(i,j)) return false;
        if (blocked[idx(i,j)]) return false;
        if (observed[idx(i,j)]) return false;
        if ((i==0 && j==N/2) || (i==ti && j==tj)) return false;
        if (!ignore_adjacent_T && hasAdjacentT(i,j)) return false;
        return is_art[idx(i,j)] == 0;
    }

    // 視界から1セル選ぶ（各視点×4方向の最短を集約）
    vector<pii> pickFromVisionAndPlace(int pi,int pj) {
        vector<pair<int,int>> sources = {{pi,pj}};
        for (int d=0; d<4; ++d) {
            int ni=pi+di4[d], nj=pj+dj4[d];
            if (inBounds(ni,nj) && !blocked[idx(ni,nj)]) sources.push_back({ni,nj});
        }

        set<pii> selected;
        for (auto [si,sj] : sources) {
            for (int d=0; d<4; ++d) {
                int ni=si+di4[d], nj=sj+dj4[d];
                pii best{-1,-1}; int bestDist=INT_MAX;
                while (inBounds(ni,nj)) {
                    if (blocked[idx(ni,nj)]) break;
                    if (canPlaceByArt(ni,nj,false)) {
                        int dist = abs(ni-si)+abs(nj-sj);
                        if (dist < bestDist) { bestDist=dist; best={ni,nj}; }
                    }
                    ni+=di4[d]; nj+=dj4[d];
                }
                if (best.first!=-1) selected.insert(best);
            }
        }

        vector<pii> placed;
        for (auto [ci,cj] : selected) {
            if (canPlaceByArt(ci,cj,false)) {
                // --- 追加仕様: この配置でゴール隣接4マスが「新たに」関節点になるなら skip ---
                // 配置前の関節点状態をスナップショット
                bool baseArt[4] = {false,false,false,false};
                for (int d=0; d<4; ++d) {
                    int gi = ti + di4[d], gj = tj + dj4[d];
                    if (inBounds(gi,gj) && !blocked[idx(gi,gj)]) {
                        baseArt[d] = (is_art[idx(gi,gj)] != 0);
                    }
                }

                // 仮配置 → 連結性OKなら関節点を再計算
                blocked[idx(ci,cj)]=1; --total_open_cells;
                bool ok = recomputeArticulation(); // 次の判定用
                if (!ok) {
                    blocked[idx(ci,cj)]=0; ++total_open_cells;
                    continue;
                }

                // ゴール隣接4マスのいずれかが「非関節点→関節点」に遷移していればロールバック＆skip
                bool goalAdjBecameArt = false;
                for (int d=0; d<4; ++d) {
                    int gi = ti + di4[d], gj = tj + dj4[d];
                    if (inBounds(gi,gj) && !blocked[idx(gi,gj)]) {
                        unsigned char nowArt = is_art[idx(gi,gj)];
                        if (!baseArt[d] && nowArt) { goalAdjBecameArt = true; break; }
                    }
                }
                if (goalAdjBecameArt) {
                    blocked[idx(ci,cj)]=0; ++total_open_cells;
                    continue; // ← 追加仕様
                }

                // 条件を満たすので確定
                placed.push_back({ci,cj});
            }
        }
        return placed;
    }

    vector<pair<int,int>> tryPlaceGoalProtection(int pi,int pj) {
        vector<pair<int,int>> sources = {}, ret;
        for (int d=0; d<4; ++d) {
            int ni=pi+di4[d], nj=pj+dj4[d];
            if (inBounds(ni,nj) && !blocked[idx(ni,nj)]) sources.push_back({ni,nj});
        }

        // (ti,tj) から見えるマスの一覧を取得
        vector<bool> can_see_goal(N*N,false);
		can_see_goal[idx(ti,tj)] = true; // ゴール自体は常に見える
        for (int d=0; d<4; ++d) {
            int ni=ti+di4[d], nj=tj+dj4[d];
            while (inBounds(ni,nj)) {
                if (blocked[idx(ni,nj)]) break;
                can_see_goal[idx(ni,nj)] = true;
                ni+=di4[d]; nj+=dj4[d];
				break; // 切った方がなんか良さそう、なんでだ？？？？
            }
        }

        for (auto [si,sj] : sources) {
            for (int d=0; d<4; ++d) {
                int ni=si+di4[d], nj=sj+dj4[d];
                cerr<< "try goal protection from: " << si << " " << sj << " dir=" << d << endl;
                while (inBounds(ni,nj)) {
                    if(can_see_goal[idx(ni,nj)]) {
                        cerr<< " can see goal: " << ni << " " << nj << endl;
                        int rd=d^1; int gi=ni, gj=nj;
                        while (inBounds(gi,gj)) {
                            if (blocked[idx(gi,gj)]) break;
                            if (!observed[idx(gi,gj)] && !blocked[idx(gi,gj)] && !(gi==0 && gj==N/2)) {
                                blocked[idx(gi,gj)]=1; --total_open_cells;
                                bool ok=recomputeArticulation();
                                if (ok) {
                                    ret.push_back({gi,gj});
                                    cerr << "goal protection candidate: " << si << " " << sj << " " << d << " -> " << gi << " " << gj << endl;
                                    goto NEXT_DIRECTION;
                                }
                                blocked[idx(gi,gj)]=0; ++total_open_cells;
                            }
                            gi+=di4[rd]; gj+=dj4[rd];
                        }
						break;
					}
                    if (blocked[idx(ni,nj)]) break;
                    ni+=di4[d]; nj+=dj4[d];
                }
                NEXT_DIRECTION: ;
            }
        }
        return ret;
    }

public:
    void readInitialInput() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> N >> ti >> tj;
        blocked.assign(N*N,0);
        observed.assign(N*N,0);
        visited.assign(N*N,0);

        string s;
        for (int i=0;i<N;++i){
            cin >> s;
            for (int j=0;j<N;++j){
                if (s[j]=='T'){ blocked[idx(i,j)]=1; }
                else ++total_open_cells;
            }
        }

        disc.assign(N*N,-1); low.assign(N*N,0);
        parent.assign(N*N,-1); is_art.assign(N*N,0);

        observed[idx(0,N/2)]=1;
		//  visited[idx(0,N/2)]=1;
    }

    void processTurn(int pi,int pj, const vector<pii>& obsIn){
        static int turn=1;
        for (auto [oi,oj]: obsIn) observed[idx(oi,oj)]=1;
        if (visited[idx(pi,pj)]) { cout<<"0\n"<<flush; ++turn; return; }
        visited[idx(pi,pj)]=1;
        for (auto [oi,oj]: obsIn) observed[idx(oi,oj)]=1;

        {
            cerr<<"observed: "<<obsIn.size()<<endl;
            for(auto [oi,oj]: obsIn) cerr<<oi<<" "<<oj<<" ";
            cerr<<endl;
        }

        bool feasible = recomputeArticulation();
        if (!feasible){ cout<<"0\n"<<flush; ++turn; return; }


        auto gp = tryPlaceGoalProtection(pi,pj);
        if (!gp.empty()) {
            cout << gp.size();
            for (auto [i,j]: gp) cout << " " << i << " " << j;
            cout << "\n" << flush;
            cerr<<"goal protection placed: "<<gp.size()<<endl;
            for(auto [i,j]: gp) cerr<<i<<" "<<j<<" ";
            cerr<<endl;
            ++turn;
            return;
        }


        auto placed = pickFromVisionAndPlace(pi,pj);

        cout << placed.size();
        for (auto [i,j]: placed) cout << " " << i << " " << j;
        cout << "\n" << flush;

        cerr<<"turn "<<turn<<" placed: "<<placed.size()<<endl;
        for(auto [i,j]: placed) cerr<<i<<" "<<j<<" ";
        cerr<<endl;

        ++turn;
    }

    void runInteractive() {
        readInitialInput();
        while (true) {
            int pi,pj,k;
            if (!(cin>>pi>>pj>>k)) break;
            if (pi==ti && pj==tj) break;
            if (pi==-1) break;
            vector<pii> obs; obs.reserve(k);
            for (int t=0;t<k;++t){ int oi,oj; cin>>oi>>oj; obs.push_back({oi,oj}); }
            processTurn(pi,pj,obs);
        }
    }
};

int main(){
    VisionFirstTrentPlacer solver;
    solver.runInteractive();
    return 0;
}
