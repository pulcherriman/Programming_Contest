const gulp = require('gulp');
const inlinesource = require('gulp-inline-source');
const replace = require('gulp-replace');
const del = require('del');

gulp.task('pack', (done) => {
  gulp
    .src('./build/*.html')
    .pipe(replace('.js"></script>', '.js" inline></script>'))
    .pipe(replace('rel="stylesheet">', 'rel="stylesheet" inline>'))
    .pipe(
      inlinesource({
        compress: false,
        ignore: ['png'],
      })
    )
    .pipe(gulp.dest('./build'));
  done();
});

gulp.task('clean', () => {
  return del(['build/static', 'build/asset-manifest.json'], { force: true });
});
