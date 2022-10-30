module.exports = {
    mode: 'production',
    // mode: 'development',

    optimization: {
        minimize: true
    },

    entry: './src/index.ts',
    output: {
        filename: './index.js'
    },

    module: {
        rules: [
            {
                test: /\.ts$/,
                use: 'ts-loader',
            },
        ],
    },

    resolve: {
        extensions: [
            '.ts', '.js',
        ],
    },
};