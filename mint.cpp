template<ll _MOD=MOD>class modint {
public:
	modint() {this->number = 0;}
	modint(const ll src) {this->number = opposit(src);}
	modint(const modint<_MOD> &src) {this->number = src.number;}
	modint<_MOD>& operator += (const modint<_MOD>& obj) {
		this->number = san2(this->number + obj.number);
		return *this;
	}
	modint<_MOD>& operator -= (const modint<_MOD>& obj) {
		this->number = san2(this->number - obj.number + _MOD);
		return *this;
	}
	modint<_MOD>& operator *= (const modint<_MOD>& obj) {
		this->number = (this->number * obj.number) % _MOD;
		return *this;
	}
	modint<_MOD>& operator /= (const modint<_MOD>& obj) {
		this->number = (this->number * inverse(obj.number)) % _MOD;
		return *this;
	}
	modint<_MOD>& operator += (const ll n) {
		this->number = san2(this->number + opposit(n));
		return *this;
	}
	modint<_MOD>& operator -= (const ll n) {
		this->number = san2(this->number - opposit(n) + _MOD);
		return *this;
	}
	modint<_MOD>& operator *= (const ll n) {
		this->number = (this->number * opposit(n)) % _MOD;
		return *this;
	}
	modint<_MOD>& operator /= (const ll n) {
		this->number = (this->number * inverse(n)) % _MOD;
		return *this;
	}
	modint<_MOD> operator + (const modint<_MOD> obj) { modint<_MOD>re(*this); return re += obj; }
	modint<_MOD> operator - (const modint<_MOD> obj) { modint<_MOD>re(*this); return re -= obj; }
	modint<_MOD> operator * (const modint<_MOD> obj) { modint<_MOD>re(*this); return re *= obj; }
	modint<_MOD> operator / (const modint<_MOD> obj) { modint<_MOD>re(*this); return re /= obj; }
	modint<_MOD> operator + (const ll n) { modint<_MOD>re(*this); return re += n; }
	modint<_MOD> operator - (const ll n) { modint<_MOD>re(*this); return re -= n; }
	modint<_MOD> operator * (const ll n) { modint<_MOD>re(*this); return re *= n; }
	modint<_MOD> operator / (const ll n) { modint<_MOD>re(*this); return re /= n; }
 
	modint<_MOD> operator = (const ll n) {
		this->number = opposit(n);
		return *this;
	}
	ll get() {return number;}
	friend ostream& operator<<(ostream&os, const modint& obj){return os<<obj.number;}
private:
	ll number;
	ll opposit(ll n) {
		if (n < 0)n = _MOD - ((-n) % _MOD);
		return n % _MOD;
	}
	ll inverse(ll n) {
		n = opposit(n);
		ll result = 1;
		for (ll i = _MOD - 2; i; i /= 2) {
			if (i % 2)result = (result * n) % _MOD;
			n = (n * n) % _MOD;
		}
		return result;
	}
	inline ll san2(const ll n) {return _MOD <= n ? n - _MOD : n;}
};
using mint=modint<>;