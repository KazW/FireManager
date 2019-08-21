import svelte from 'rollup-plugin-svelte';
import resolve from 'rollup-plugin-node-resolve';
import commonjs from 'rollup-plugin-commonjs';
import livereload from 'rollup-plugin-livereload';
import { terser } from 'rollup-plugin-terser';
import htmlTemplate from 'rollup-plugin-generate-html-template';
import copy from 'rollup-plugin-copy';
import typescript from 'rollup-plugin-typescript';
import postcss from 'rollup-plugin-postcss';
import replace from 'rollup-plugin-replace';
import gzip from 'rollup-plugin-gzip'

const production = !process.env.ROLLUP_WATCH;

let build_path;
if (production) {
  build_path = '../FireManager_firmware/data/web';
} else {
  build_path = 'build';
}

export default {
  input: 'app/ts/main.ts',
  output: {
    sourcemap: !production,
    format: 'iife',
    name: 'app',
    file: build_path + '/main.js'
  },
  plugins: [
    svelte({
      // enable run-time checks when not in production
      dev: !production,
      // we'll extract any component CSS out into
      // a separate file — better for performance
      css: css => {
        css.write(build_path + '/bundle.css');
      }
    }),

    // If you have external dependencies installed from
    // npm, you'll most likely need these plugins. In
    // some cases you'll need additional configuration —
    // consult the documentation for details:
    // https://github.com/rollup/rollup-plugin-commonjs
    resolve({
      browser: true,
      dedupe: importee => importee === 'svelte' || importee.startsWith('svelte/')
    }),
    commonjs(),

    // Watch the `web` directory and refresh the
    // browser on changes when not in production
    !production && livereload(build_path),

    // If we're building for production (npm run build
    // instead of npm run dev), minify
    production && terser(),
    htmlTemplate({
      template: 'app/html/main.html',
      target: 'index.html',
    }),
    copy({
      targets: [
        { src: 'app/static/*', dest: build_path },
        {
          src: [
            'node_modules/@fortawesome/fontawesome-free/webfonts/*',
            '!**/*.ttf',
            '!**/*.eot',
            '!**/*.svg'
          ],
          dest: build_path
        }
      ],
      verbose: true
    }),
    typescript(),
    postcss({
      extract: true
    }),
    replace({
      __API_URL__: production ? '' : process.env.API_URL,
    }),
    production && gzip({
      additionalFilesDelay: 1,
      additionalFiles: [
        '../FireManager_firmware/data/web/bundle.css',
        '../FireManager_firmware/data/web/favicon.png',
        '../FireManager_firmware/data/web/fa-solid-900.woff',
        '../FireManager_firmware/data/web/fa-solid-900.woff2',
        '../FireManager_firmware/data/web/fa-regular-400.woff',
        '../FireManager_firmware/data/web/fa-regular-400.woff2',
        '../FireManager_firmware/data/web/fa-brands-400.woff',
        '../FireManager_firmware/data/web/fa-brands-400.woff2'
      ]
    })
  ],
  watch: {
    clearScreen: false
  }
};
