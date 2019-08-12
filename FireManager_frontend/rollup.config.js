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

export default {
  input: 'app/ts/main.ts',
  output: {
    sourcemap: !production,
    format: 'iife',
    name: 'app',
    file: '../firmware/data/web/main.js'
  },
  plugins: [
    svelte({
      // enable run-time checks when not in production
      dev: !production,
      // we'll extract any component CSS out into
      // a separate file — better for performance
      css: css => {
        css.write('../firmware/data/web/bundle.css');
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
    !production && livereload('../firmware/data/web'),

    // If we're building for production (npm run build
    // instead of npm run dev), minify
    production && terser(),
    htmlTemplate({
      template: 'app/html/main.html',
      target: 'index.html',
    }),
    copy({
      targets: [
        { src: 'app/static/*', dest: '../firmware/data/web' },
        {
          src: [
            'node_modules/@fortawesome/fontawesome-free/webfonts/*',
            '!**/*.ttf',
            '!**/*.eot',
            '!**/*.svg'
          ],
          dest: '../firmware/data/web'
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
    production && gzip({ filter: /\.(js|woff|woff2|json|css|png|html)$/ })
  ],
  watch: {
    clearScreen: false
  }
};
