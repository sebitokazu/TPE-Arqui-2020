/*!--------------------------------------------------------
 * Copyright (C) Microsoft Corporation. All rights reserved.
 *--------------------------------------------------------*/
(function(){var e=["require","exports","vs/base/common/path","os","fs","vs/base/common/platform","vs/base/common/process","vs/base/node/terminalEncoding","child_process","vs/nls!vs/platform/environment/node/argv","vs/platform/environment/node/argv","vs/platform/environment/node/stdin","vs/platform/environment/node/waitMarkerFile","vs/nls","vs/nls!vs/server/remoteCli","minimist","vs/server/remoteCli","url","http"],t=function(t){for(var n=[],o=0,i=t.length;o<i;o++)n[o]=e[t[o]];return n};define(e[5],t([0,1]),(function(e,t){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.isLittleEndian=t.OS=t.OperatingSystem=t.setImmediate=t.globals=t.translationsConfigFile=t.locale=t.Language=t.language=t.isRootUser=t.userAgent=t.platform=t.isIOS=t.isWeb=t.isNative=t.isLinux=t.isMacintosh=t.isWindows=t.PlatformToString=t.Platform=void 0;let n=!1,o=!1,i=!1,r=!1,s=!1,l=!1,a=void 0,c="en",d=void 0,p=void 0
;const f="undefined"!=typeof process&&void 0!==process.versions&&void 0!==process.versions.electron&&"renderer"===process.type;if("object"!=typeof navigator||f){if("object"==typeof process){n="win32"===process.platform,o="darwin"===process.platform,i="linux"===process.platform,a="en",c="en";const e=process.env.VSCODE_NLS_CONFIG;if(e)try{const t=JSON.parse(e),n=t.availableLanguages["*"];a=t.locale,c=n||"en",d=t._translationsConfigFile}catch(e){}r=!0}}else p=navigator.userAgent,n=p.indexOf("Windows")>=0,o=p.indexOf("Macintosh")>=0,l=p.indexOf("Macintosh")>=0&&!!navigator.maxTouchPoints&&navigator.maxTouchPoints>0,i=p.indexOf("Linux")>=0,s=!0,c=a=navigator.language;!function(e){e[e.Web=0]="Web",e[e.Mac=1]="Mac",e[e.Linux=2]="Linux",e[e.Windows=3]="Windows"}(t.Platform||(t.Platform={})),t.PlatformToString=function(e){switch(e){case 0:return"Web";case 1:return"Mac";case 2:return"Linux";case 3:return"Windows"}};let u=0;o?u=1:n?u=3:i&&(u=2),t.isWindows=n,t.isMacintosh=o,t.isLinux=i,t.isNative=r,t.isWeb=s,t.isIOS=l,
t.platform=u,t.userAgent=p,t.isRootUser=function(){return r&&!n&&0===process.getuid()},t.language=c,function(e){e.value=function(){return t.language},e.isDefaultVariant=function(){return 2===t.language.length?"en"===t.language:t.language.length>=3&&("e"===t.language[0]&&"n"===t.language[1]&&"-"===t.language[2])},e.isDefault=function(){return"en"===t.language}}(t.Language||(t.Language={})),t.locale=a,t.translationsConfigFile=d;const g="object"==typeof self?self:"object"==typeof global?global:{};t.globals=g,t.setImmediate=function(){if(t.globals.setImmediate)return t.globals.setImmediate.bind(t.globals);if("function"==typeof t.globals.postMessage&&!t.globals.importScripts){let e=[];t.globals.addEventListener("message",t=>{if(t.data&&t.data.vscodeSetImmediateId)for(let n=0,o=e.length;n<o;n++){const o=e[n];if(o.id===t.data.vscodeSetImmediateId)return e.splice(n,1),void o.callback()}});let n=0;return o=>{const i=++n;e.push({id:i,callback:o}),t.globals.postMessage({vscodeSetImmediateId:i},"*")}}
if("undefined"!=typeof process&&"function"==typeof process.nextTick)return process.nextTick.bind(process);const e=Promise.resolve();return t=>e.then(t)}(),function(e){e[e.Windows=1]="Windows",e[e.Macintosh=2]="Macintosh",e[e.Linux=3]="Linux"}(t.OperatingSystem||(t.OperatingSystem={})),t.OS=o?2:n?1:3;let h=!0,m=!1;t.isLittleEndian=function(){if(!m){m=!0;const e=new Uint8Array(2);e[0]=1,e[1]=2;const t=new Uint16Array(e.buffer);h=513===t[0]}return h}})),define(e[6],t([0,1,5]),(function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.nextTick=t.platform=t.env=t.cwd=void 0;const o="undefined"==typeof process?{cwd:()=>"/",env:Object.create(null),get platform(){return n.isWindows?"win32":n.isMacintosh?"darwin":"linux"},nextTick:e=>n.setImmediate(e)}:process;t.cwd=o.cwd,t.env=o.env,t.platform=o.platform,t.nextTick=o.nextTick})),define(e[2],t([0,1,6]),(function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),
t.delimiter=t.sep=t.toNamespacedPath=t.parse=t.format=t.extname=t.basename=t.dirname=t.relative=t.resolve=t.join=t.isAbsolute=t.normalize=t.posix=t.win32=void 0;const o=65,i=97,r=90,s=122,l=46,a=47,c=92;class d extends Error{constructor(e,t,n){let o;"string"==typeof t&&0===t.indexOf("not ")?(o="must not be",t=t.replace(/^not /,"")):o="must be";const i=-1!==e.indexOf(".")?"property":"argument";let r=`The "${e}" ${i} ${o} of type ${t}`;super(r+=`. Received type ${typeof n}`),this.code="ERR_INVALID_ARG_TYPE"}}function p(e,t){if("string"!=typeof e)throw new d(t,"string",e)}function f(e){return e===a||e===c}function u(e){return e===a}function g(e){return e>=o&&e<=r||e>=i&&e<=s}function h(e,t,n,o){let i="",r=0,s=-1,c=0,d=0;for(let p=0;p<=e.length;++p){if(p<e.length)d=e.charCodeAt(p);else{if(o(d))break;d=a}if(o(d)){if(s===p-1||1===c);else if(2===c){if(i.length<2||2!==r||i.charCodeAt(i.length-1)!==l||i.charCodeAt(i.length-2)!==l){if(i.length>2){const e=i.lastIndexOf(n);-1===e?(i="",
r=0):r=(i=i.slice(0,e)).length-1-i.lastIndexOf(n),s=p,c=0;continue}if(0!==i.length){i="",r=0,s=p,c=0;continue}}t&&(i+=i.length>0?`${n}..`:"..",r=2)}else i.length>0?i+=`${n}${e.slice(s+1,p)}`:i=e.slice(s+1,p),r=p-s-1;s=p,c=0}else d===l&&-1!==c?++c:c=-1}return i}function m(e,t){if(null===t||"object"!=typeof t)throw new d("pathObject","Object",t);const n=t.dir||t.root,o=t.base||`${t.name||""}${t.ext||""}`;return n?n===t.root?`${n}${o}`:`${n}${e}${o}`:o}t.win32={resolve(...e){let t="",o="",i=!1;for(let r=e.length-1;r>=-1;r--){let s;if(r>=0){if(p(s=e[r],"path"),0===s.length)continue}else 0===t.length?s=n.cwd():(void 0===(s=n.env[`=${t}`]||n.cwd())||s.slice(0,2).toLowerCase()!==t.toLowerCase()&&s.charCodeAt(2)===c)&&(s=`${t}\\`);const l=s.length;let a=0,d="",u=!1;const h=s.charCodeAt(0);if(1===l)f(h)&&(a=1,u=!0);else if(f(h))if(u=!0,f(s.charCodeAt(1))){let e=2,t=e;for(;e<l&&!f(s.charCodeAt(e));)e++;if(e<l&&e!==t){const n=s.slice(t,e);for(t=e;e<l&&f(s.charCodeAt(e));)e++;if(e<l&&e!==t){
for(t=e;e<l&&!f(s.charCodeAt(e));)e++;e!==l&&e===t||(d=`\\\\${n}\\${s.slice(t,e)}`,a=e)}}}else a=1;else g(h)&&58===s.charCodeAt(1)&&(d=s.slice(0,2),a=2,l>2&&f(s.charCodeAt(2))&&(u=!0,a=3));if(d.length>0)if(t.length>0){if(d.toLowerCase()!==t.toLowerCase())continue}else t=d;if(i){if(t.length>0)break}else if(o=`${s.slice(a)}\\${o}`,i=u,u&&t.length>0)break}return o=h(o,!i,"\\",f),i?`${t}\\${o}`:`${t}${o}`||"."},normalize(e){p(e,"path");const t=e.length;if(0===t)return".";let n,o=0,i=!1;const r=e.charCodeAt(0);if(1===t)return u(r)?"\\":e;if(f(r))if(i=!0,f(e.charCodeAt(1))){let i=2,r=i;for(;i<t&&!f(e.charCodeAt(i));)i++;if(i<t&&i!==r){const s=e.slice(r,i);for(r=i;i<t&&f(e.charCodeAt(i));)i++;if(i<t&&i!==r){for(r=i;i<t&&!f(e.charCodeAt(i));)i++;if(i===t)return`\\\\${s}\\${e.slice(r)}\\`;i!==r&&(n=`\\\\${s}\\${e.slice(r,i)}`,o=i)}}}else o=1;else g(r)&&58===e.charCodeAt(1)&&(n=e.slice(0,2),o=2,t>2&&f(e.charCodeAt(2))&&(i=!0,o=3));let s=o<t?h(e.slice(o),!i,"\\",f):"";return 0!==s.length||i||(s="."),
s.length>0&&f(e.charCodeAt(t-1))&&(s+="\\"),void 0===n?i?`\\${s}`:s:i?`${n}\\${s}`:`${n}${s}`},isAbsolute(e){p(e,"path");const t=e.length;if(0===t)return!1;const n=e.charCodeAt(0);return f(n)||t>2&&g(n)&&58===e.charCodeAt(1)&&f(e.charCodeAt(2))},join(...e){if(0===e.length)return".";let n,o;for(let t=0;t<e.length;++t){const i=e[t];p(i,"path"),i.length>0&&(void 0===n?n=o=i:n+=`\\${i}`)}if(void 0===n)return".";let i=!0,r=0;if("string"==typeof o&&f(o.charCodeAt(0))){++r;const e=o.length;e>1&&f(o.charCodeAt(1))&&(++r,e>2&&(f(o.charCodeAt(2))?++r:i=!1))}if(i){for(;r<n.length&&f(n.charCodeAt(r));)r++;r>=2&&(n=`\\${n.slice(r)}`)}return t.win32.normalize(n)},relative(e,n){if(p(e,"from"),p(n,"to"),e===n)return"";const o=t.win32.resolve(e),i=t.win32.resolve(n);if(o===i)return"";if((e=o.toLowerCase())===(n=i.toLowerCase()))return"";let r=0;for(;r<e.length&&e.charCodeAt(r)===c;)r++;let s=e.length;for(;s-1>r&&e.charCodeAt(s-1)===c;)s--;const l=s-r;let a=0;for(;a<n.length&&n.charCodeAt(a)===c;)a++;let d=n.length
;for(;d-1>a&&n.charCodeAt(d-1)===c;)d--;const f=d-a,u=l<f?l:f;let g=-1,h=0;for(;h<u;h++){const t=e.charCodeAt(r+h);if(t!==n.charCodeAt(a+h))break;t===c&&(g=h)}if(h!==u){if(-1===g)return i}else{if(f>u){if(n.charCodeAt(a+h)===c)return i.slice(a+h+1);if(2===h)return i.slice(a+h)}l>u&&(e.charCodeAt(r+h)===c?g=h:2===h&&(g=3)),-1===g&&(g=0)}let m="";for(h=r+g+1;h<=s;++h)h!==s&&e.charCodeAt(h)!==c||(m+=0===m.length?"..":"\\..");return a+=g,m.length>0?`${m}${i.slice(a,d)}`:(i.charCodeAt(a)===c&&++a,i.slice(a,d))},toNamespacedPath(e){if("string"!=typeof e)return e;if(0===e.length)return"";const n=t.win32.resolve(e);if(n.length<=2)return e;if(n.charCodeAt(0)===c){if(n.charCodeAt(1)===c){const e=n.charCodeAt(2);if(63!==e&&e!==l)return`\\\\?\\UNC\\${n.slice(2)}`}}else if(g(n.charCodeAt(0))&&58===n.charCodeAt(1)&&n.charCodeAt(2)===c)return`\\\\?\\${n}`;return e},dirname(e){p(e,"path");const t=e.length;if(0===t)return".";let n=-1,o=0;const i=e.charCodeAt(0);if(1===t)return f(i)?e:".";if(f(i)){if(n=o=1,f(e.charCodeAt(1))){
let i=2,r=i;for(;i<t&&!f(e.charCodeAt(i));)i++;if(i<t&&i!==r){for(r=i;i<t&&f(e.charCodeAt(i));)i++;if(i<t&&i!==r){for(r=i;i<t&&!f(e.charCodeAt(i));)i++;if(i===t)return e;i!==r&&(n=o=i+1)}}}}else g(i)&&58===e.charCodeAt(1)&&(o=n=t>2&&f(e.charCodeAt(2))?3:2);let r=-1,s=!0;for(let n=t-1;n>=o;--n)if(f(e.charCodeAt(n))){if(!s){r=n;break}}else s=!1;if(-1===r){if(-1===n)return".";r=n}return e.slice(0,r)},basename(e,t){void 0!==t&&p(t,"ext"),p(e,"path");let n,o=0,i=-1,r=!0;if(e.length>=2&&g(e.charCodeAt(0))&&58===e.charCodeAt(1)&&(o=2),void 0!==t&&t.length>0&&t.length<=e.length){if(t===e)return"";let s=t.length-1,l=-1;for(n=e.length-1;n>=o;--n){const a=e.charCodeAt(n);if(f(a)){if(!r){o=n+1;break}}else-1===l&&(r=!1,l=n+1),s>=0&&(a===t.charCodeAt(s)?-1==--s&&(i=n):(s=-1,i=l))}return o===i?i=l:-1===i&&(i=e.length),e.slice(o,i)}for(n=e.length-1;n>=o;--n)if(f(e.charCodeAt(n))){if(!r){o=n+1;break}}else-1===i&&(r=!1,i=n+1);return-1===i?"":e.slice(o,i)},extname(e){p(e,"path");let t=0,n=-1,o=0,i=-1,r=!0,s=0
;e.length>=2&&58===e.charCodeAt(1)&&g(e.charCodeAt(0))&&(t=o=2);for(let a=e.length-1;a>=t;--a){const t=e.charCodeAt(a);if(f(t)){if(!r){o=a+1;break}}else-1===i&&(r=!1,i=a+1),t===l?-1===n?n=a:1!==s&&(s=1):-1!==n&&(s=-1)}return-1===n||-1===i||0===s||1===s&&n===i-1&&n===o+1?"":e.slice(n,i)},format:m.bind(null,"\\"),parse(e){p(e,"path");const t={root:"",dir:"",base:"",ext:"",name:""};if(0===e.length)return t;const n=e.length;let o=0,i=e.charCodeAt(0);if(1===n)return f(i)?(t.root=t.dir=e,t):(t.base=t.name=e,t);if(f(i)){if(o=1,f(e.charCodeAt(1))){let t=2,i=t;for(;t<n&&!f(e.charCodeAt(t));)t++;if(t<n&&t!==i){for(i=t;t<n&&f(e.charCodeAt(t));)t++;if(t<n&&t!==i){for(i=t;t<n&&!f(e.charCodeAt(t));)t++;t===n?o=t:t!==i&&(o=t+1)}}}}else if(g(i)&&58===e.charCodeAt(1)){if(n<=2)return t.root=t.dir=e,t;if(o=2,f(e.charCodeAt(2))){if(3===n)return t.root=t.dir=e,t;o=3}}o>0&&(t.root=e.slice(0,o));let r=-1,s=o,a=-1,c=!0,d=e.length-1,u=0;for(;d>=o;--d)if(f(i=e.charCodeAt(d))){if(!c){s=d+1;break}}else-1===a&&(c=!1,a=d+1),
i===l?-1===r?r=d:1!==u&&(u=1):-1!==r&&(u=-1);return-1!==a&&(-1===r||0===u||1===u&&r===a-1&&r===s+1?t.base=t.name=e.slice(s,a):(t.name=e.slice(s,r),t.base=e.slice(s,a),t.ext=e.slice(r,a))),t.dir=s>0&&s!==o?e.slice(0,s-1):t.root,t},sep:"\\",delimiter:";",win32:null,posix:null},t.posix={resolve(...e){let t="",o=!1;for(let i=e.length-1;i>=-1&&!o;i--){const r=i>=0?e[i]:n.cwd();p(r,"path"),0!==r.length&&(t=`${r}/${t}`,o=r.charCodeAt(0)===a)}return t=h(t,!o,"/",u),o?`/${t}`:t.length>0?t:"."},normalize(e){if(p(e,"path"),0===e.length)return".";const t=e.charCodeAt(0)===a,n=e.charCodeAt(e.length-1)===a;return 0===(e=h(e,!t,"/",u)).length?t?"/":n?"./":".":(n&&(e+="/"),t?`/${e}`:e)},isAbsolute:e=>(p(e,"path"),e.length>0&&e.charCodeAt(0)===a),join(...e){if(0===e.length)return".";let n;for(let t=0;t<e.length;++t){const o=e[t];p(o,"path"),o.length>0&&(void 0===n?n=o:n+=`/${o}`)}return void 0===n?".":t.posix.normalize(n)},relative(e,n){if(p(e,"from"),p(n,"to"),e===n)return""
;if((e=t.posix.resolve(e))===(n=t.posix.resolve(n)))return"";const o=e.length,i=o-1,r=n.length-1,s=i<r?i:r;let l=-1,c=0;for(;c<s;c++){const t=e.charCodeAt(1+c);if(t!==n.charCodeAt(1+c))break;t===a&&(l=c)}if(c===s)if(r>s){if(n.charCodeAt(1+c)===a)return n.slice(1+c+1);if(0===c)return n.slice(1+c)}else i>s&&(e.charCodeAt(1+c)===a?l=c:0===c&&(l=0));let d="";for(c=1+l+1;c<=o;++c)c!==o&&e.charCodeAt(c)!==a||(d+=0===d.length?"..":"/..");return`${d}${n.slice(1+l)}`},toNamespacedPath:e=>e,dirname(e){if(p(e,"path"),0===e.length)return".";const t=e.charCodeAt(0)===a;let n=-1,o=!0;for(let t=e.length-1;t>=1;--t)if(e.charCodeAt(t)===a){if(!o){n=t;break}}else o=!1;return-1===n?t?"/":".":t&&1===n?"//":e.slice(0,n)},basename(e,t){void 0!==t&&p(t,"ext"),p(e,"path");let n,o=0,i=-1,r=!0;if(void 0!==t&&t.length>0&&t.length<=e.length){if(t===e)return"";let s=t.length-1,l=-1;for(n=e.length-1;n>=0;--n){const c=e.charCodeAt(n);if(c===a){if(!r){o=n+1;break}}else-1===l&&(r=!1,l=n+1),s>=0&&(c===t.charCodeAt(s)?-1==--s&&(i=n):(s=-1,
i=l))}return o===i?i=l:-1===i&&(i=e.length),e.slice(o,i)}for(n=e.length-1;n>=0;--n)if(e.charCodeAt(n)===a){if(!r){o=n+1;break}}else-1===i&&(r=!1,i=n+1);return-1===i?"":e.slice(o,i)},extname(e){p(e,"path");let t=-1,n=0,o=-1,i=!0,r=0;for(let s=e.length-1;s>=0;--s){const c=e.charCodeAt(s);if(c!==a)-1===o&&(i=!1,o=s+1),c===l?-1===t?t=s:1!==r&&(r=1):-1!==t&&(r=-1);else if(!i){n=s+1;break}}return-1===t||-1===o||0===r||1===r&&t===o-1&&t===n+1?"":e.slice(t,o)},format:m.bind(null,"/"),parse(e){p(e,"path");const t={root:"",dir:"",base:"",ext:"",name:""};if(0===e.length)return t;const n=e.charCodeAt(0)===a;let o;n?(t.root="/",o=1):o=0;let i=-1,r=0,s=-1,c=!0,d=e.length-1,f=0;for(;d>=o;--d){const t=e.charCodeAt(d);if(t!==a)-1===s&&(c=!1,s=d+1),t===l?-1===i?i=d:1!==f&&(f=1):-1!==i&&(f=-1);else if(!c){r=d+1;break}}if(-1!==s){const o=0===r&&n?1:r;-1===i||0===f||1===f&&i===s-1&&i===r+1?t.base=t.name=e.slice(o,s):(t.name=e.slice(o,i),t.base=e.slice(o,s),t.ext=e.slice(i,s))}return r>0?t.dir=e.slice(0,r-1):n&&(t.dir="/"),t},
sep:"/",delimiter:":",win32:null,posix:null},t.posix.win32=t.win32.win32=t.win32,t.posix.posix=t.win32.posix=t.posix,t.normalize="win32"===n.platform?t.win32.normalize:t.posix.normalize,t.isAbsolute="win32"===n.platform?t.win32.isAbsolute:t.posix.isAbsolute,t.join="win32"===n.platform?t.win32.join:t.posix.join,t.resolve="win32"===n.platform?t.win32.resolve:t.posix.resolve,t.relative="win32"===n.platform?t.win32.relative:t.posix.relative,t.dirname="win32"===n.platform?t.win32.dirname:t.posix.dirname,t.basename="win32"===n.platform?t.win32.basename:t.posix.basename,t.extname="win32"===n.platform?t.win32.extname:t.posix.extname,t.format="win32"===n.platform?t.win32.format:t.posix.format,t.parse="win32"===n.platform?t.win32.parse:t.posix.parse,t.toNamespacedPath="win32"===n.platform?t.win32.toNamespacedPath:t.posix.toNamespacedPath,t.sep="win32"===n.platform?t.win32.sep:t.posix.sep,t.delimiter="win32"===n.platform?t.win32.delimiter:t.posix.delimiter})),define(e[7],t([0,1,8,3]),(function(e,t,n,o){"use strict"
;Object.defineProperty(t,"__esModule",{value:!0}),t.resolveTerminalEncoding=void 0;const i={437:"cp437",850:"cp850",852:"cp852",855:"cp855",857:"cp857",860:"cp860",861:"cp861",863:"cp863",865:"cp865",866:"cp866",869:"cp869",936:"cp936",1252:"cp1252"};const r={ibm866:"cp866",big5:"cp950"},s="utf8";t.resolveTerminalEncoding=async function(e){let t;const l=process.env.VSCODE_CLI_ENCODING;l?(e&&console.log(`Found VSCODE_CLI_ENCODING variable: ${l}`),t=Promise.resolve(l)):t="win32"===o.platform()?new Promise(t=>{e&&console.log('Running "chcp" to detect terminal encoding...'),n.exec("chcp",(e,n,o)=>{if(n){const e=Object.keys(i);for(const o of e)if(n.indexOf(o)>=0)return t(i[o])}return t(void 0)})}):new Promise(t=>{e&&console.log('Running "locale charmap" to detect terminal encoding...'),n.exec("locale charmap",(e,n,o)=>t(n))});const a=await t;return e&&console.log(`Detected raw terminal encoding: ${a}`),a&&"utf-8"!==a.toLowerCase()&&a.toLowerCase()!==s?function(e){const t=e.replace(/[^a-zA-Z0-9]/g,"").toLowerCase()
;return r[t]||t}(a):s}})),define(e[9],t([13,14]),(function(e,t){return e.create("vs/platform/environment/node/argv",t)})),define(e[10],t([0,1,15,3,9]),(function(e,t,n,o,i){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.buildVersionMessage=t.buildHelpMessage=t.formatOptions=t.parseArgs=t.OPTIONS=void 0;const r={o:i.localize(0,null),e:i.localize(1,null),t:i.localize(2,null)};t.OPTIONS={diff:{type:"boolean",cat:"o",alias:"d",args:["file","file"],description:i.localize(3,null)},add:{type:"boolean",cat:"o",alias:"a",args:"folder",description:i.localize(4,null)},goto:{type:"boolean",cat:"o",alias:"g",args:"file:line[:character]",description:i.localize(5,null)},"new-window":{type:"boolean",cat:"o",alias:"n",description:i.localize(6,null)},"reuse-window":{type:"boolean",cat:"o",alias:"r",description:i.localize(7,null)},"folder-uri":{type:"string[]",cat:"o",args:"uri",description:i.localize(8,null)},"file-uri":{type:"string[]",cat:"o",args:"uri",description:i.localize(9,null)},wait:{type:"boolean",
cat:"o",alias:"w",description:i.localize(10,null)},waitMarkerFilePath:{type:"string"},locale:{type:"string",cat:"o",args:"locale",description:i.localize(11,null)},"user-data-dir":{type:"string",cat:"o",args:"dir",description:i.localize(12,null)},help:{type:"boolean",cat:"o",alias:"h",description:i.localize(13,null)},"extensions-dir":{type:"string",deprecates:"extensionHomePath",cat:"e",args:"dir",description:i.localize(14,null)},"extensions-download-dir":{type:"string"},"builtin-extensions-dir":{type:"string"},"list-extensions":{type:"boolean",cat:"e",description:i.localize(15,null)},"show-versions":{type:"boolean",cat:"e",description:i.localize(16,null)},category:{type:"string",cat:"e",description:i.localize(17,null)},"install-extension":{type:"string[]",cat:"e",args:"extension-id | path-to-vsix",description:i.localize(18,null)},"uninstall-extension":{type:"string[]",cat:"e",args:"extension-id",description:i.localize(19,null)},"enable-proposed-api":{type:"string[]",cat:"e",args:"extension-id",
description:i.localize(20,null)},version:{type:"boolean",cat:"t",alias:"v",description:i.localize(21,null)},verbose:{type:"boolean",cat:"t",description:i.localize(22,null)},log:{type:"string",cat:"t",args:"level",description:i.localize(23,null)},status:{type:"boolean",alias:"s",cat:"t",description:i.localize(24,null)},"prof-startup":{type:"boolean",cat:"t",description:i.localize(25,null)},"prof-append-timers":{type:"string"},"prof-startup-prefix":{type:"string"},"disable-extensions":{type:"boolean",deprecates:"disableExtensions",cat:"t",description:i.localize(26,null)},"disable-extension":{type:"string[]",cat:"t",args:"extension-id",description:i.localize(27,null)},sync:{type:"string",cat:"t",description:i.localize(28,null),args:["on","off"]},"inspect-extensions":{type:"string",deprecates:"debugPluginHost",args:"port",cat:"t",description:i.localize(29,null)},"inspect-brk-extensions":{type:"string",deprecates:"debugBrkPluginHost",args:"port",cat:"t",description:i.localize(30,null)},"disable-gpu":{
type:"boolean",cat:"t",description:i.localize(31,null)},"max-memory":{type:"string",cat:"t",description:i.localize(32,null)},telemetry:{type:"boolean",cat:"t",description:i.localize(33,null)},remote:{type:"string"},"locate-extension":{type:"string[]"},extensionDevelopmentPath:{type:"string[]"},extensionTestsPath:{type:"string"},debugId:{type:"string"},"inspect-search":{type:"string",deprecates:"debugSearch"},"inspect-brk-search":{type:"string",deprecates:"debugBrkSearch"},"export-default-configuration":{type:"string"},"install-source":{type:"string"},driver:{type:"string"},logExtensionHostCommunication:{type:"boolean"},"skip-release-notes":{type:"boolean"},"disable-restore-windows":{type:"boolean"},"disable-telemetry":{type:"boolean"},"disable-updates":{type:"boolean"},"disable-crash-reporter":{type:"boolean"},"disable-user-env-probe":{type:"boolean"},"skip-add-to-recently-opened":{type:"boolean"},"unity-launch":{type:"boolean"},"open-url":{type:"boolean"},"file-write":{type:"boolean"},"file-chmod":{
type:"boolean"},"driver-verbose":{type:"boolean"},force:{type:"boolean"},trace:{type:"boolean"},"trace-category-filter":{type:"string"},"trace-options":{type:"string"},"force-user-env":{type:"boolean"},"no-proxy-server":{type:"boolean"},"proxy-server":{type:"string"},"proxy-bypass-list":{type:"string"},"proxy-pac-url":{type:"string"},"js-flags":{type:"string"},inspect:{type:"string"},"inspect-brk":{type:"string"},nolazy:{type:"boolean"},"force-device-scale-factor":{type:"string"},"force-renderer-accessibility":{type:"boolean"},"ignore-certificate-errors":{type:"boolean"},"allow-insecure-localhost":{type:"boolean"},"log-net-log":{type:"string"},_urls:{type:"string[]"},_:{type:"string[]"}};const s={onUnknownOption:()=>{},onMultipleValues:()=>{}};function l(e,t){let n="";return t.args&&(n=Array.isArray(t.args)?` <${t.args.join("> <")}>`:` <${t.args}>`),t.alias?`-${t.alias} --${e}${n}`:`--${e}${n}`}function a(e,t){let n=0,o=[];for(const t in e){const i=e[t],r=l(t,i);n=Math.max(n,r.length),
o.push([r,i.description])}let i=n+2+1;if(t-i<25)return o.reduce((e,t)=>e.concat([`  ${t[0]}`,`      ${t[1]}`]),[]);let r=t-i-1,s=[];for(const e of o){let t=e[0],n=d(e[1],r),o=c(i-t.length-2);s.push("  "+t+o+n[0]);for(let e=1;e<n.length;e++)s.push(c(i)+n[e])}return s}function c(e){return" ".repeat(e)}function d(e,t){let n=[];for(;e.length;){let o=e.length<t?e.length:e.lastIndexOf(" ",t),i=e.slice(0,o).trim();e=e.slice(o),n.push(i)}return n}t.parseArgs=function(e,t,o=s){const i={},r=[],l=[];for(let e in t){if("_"===e[0])continue;const n=t[e];n.alias&&(i[e]=n.alias),"string"===n.type||"string[]"===n.type?(r.push(e),n.deprecates&&r.push(n.deprecates)):"boolean"===n.type&&(l.push(e),n.deprecates&&l.push(n.deprecates))}const a=n(e,{string:r,boolean:l,alias:i}),c={},d=a;c._=a._.filter(e=>e.length>0),delete d._;for(let e in t){const n=t[e];n.alias&&delete d[n.alias];let i=d[e];n.deprecates&&d.hasOwnProperty(n.deprecates)&&(i||(i=d[n.deprecates]),delete d[n.deprecates]),
void 0!==i&&("string[]"===n.type?i&&!Array.isArray(i)&&(i=[i]):"string"===n.type&&Array.isArray(i)&&(i=i.pop(),o.onMultipleValues(e,i)),c[e]=i),delete d[e]}for(let e in d)o.onUnknownOption(e);return c},t.formatOptions=a,t.buildHelpMessage=function(e,t,n,s,l=!0){const c=process.stdout.isTTY&&process.stdout.columns||80;let d=[`${e} ${n}`];d.push(""),d.push(`${i.localize(34,null)}: ${t} [${i.localize(35,null)}][${i.localize(36,null)}...]`),d.push(""),l&&("win32"===o.platform()?d.push(i.localize(37,null,t)):d.push(i.localize(38,null,t)),d.push(""));const p={};for(const e in s){const t=s[e];if(t.description&&t.cat){let n=p[t.cat];n||(p[t.cat]=n={}),n[e]=t}}for(let e in p){const t=e;let n=p[t];n&&(d.push(r[t]),d.push(...a(n,c)),d.push(""))}return d.join("\n")},t.buildVersionMessage=function(e,t){return`${e||i.localize(39,null)}\n${t||i.localize(40,null)}\n${process.arch}`}})),define(e[11],t([0,1,2,4,3,7]),(function(e,t,n,o,i,r){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),
t.readFromStdin=t.getStdinFilePath=t.stdinDataListener=t.hasStdinWithoutTty=void 0,t.hasStdinWithoutTty=function(){try{return!process.stdin.isTTY}catch(e){}return!1},t.stdinDataListener=function(e){return new Promise(t=>{const n=()=>t(!0);setTimeout(()=>{process.stdin.removeListener("data",n),t(!1)},e),process.stdin.once("data",n)})},t.getStdinFilePath=function(){return n.join(i.tmpdir(),`code-stdin-${Math.random().toString(36).replace(/[^a-z]+/g,"").substr(0,3)}.txt`)},t.readFromStdin=async function(t,n){const i=o.createWriteStream(t);let s=await r.resolveTerminalEncoding(n);const l=await new Promise((t,n)=>{e(["iconv-lite"],t,n)});l.encodingExists(s)||(console.log(`Unsupported terminal encoding: ${s}, falling back to UTF-8.`),s="utf8");const a=l.decodeStream(s);process.stdin.pipe(a).pipe(i)}})),define(e[12],t([0,1,2,3,4]),(function(e,t,n,o,i){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.createWaitMarkerFile=void 0,t.createWaitMarkerFile=function(e){
const t=n.join(o.tmpdir(),Math.random().toString(36).replace(/[^a-z]+/g,"").substr(0,10));try{return i.writeFileSync(t,""),e&&console.log(`Marker file for --wait created: ${t}`),t}catch(t){return void(e&&console.error(`Failed to create marker file for --wait: ${t}`))}}})),define(e[16],t([0,1,4,17,8,18,2,10,12,11]),(function(e,t,n,o,i,r,s,l,a,c){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.main=void 0;const d=e=>{switch(e){case"user-data-dir":case"extensions-dir":case"list-extensions":case"install-extension":case"uninstall-extension":case"show-versions":case"export-default-configuration":case"install-source":case"driver":return!1;default:return!0}},p=e=>{switch(e){case"version":case"help":case"folder-uri":case"file-uri":case"diff":case"wait":case"goto":case"reuse-window":case"new-window":case"status":return!0;default:return!1}},f=process.env.VSCODE_IPC_HOOK_CLI,u=process.env.VSCODE_CLIENT_COMMAND,g=process.env.VSCODE_CLIENT_COMMAND_CWD,h=process.env.VSCODE_CLI_AUTHORITY;function m(e,t){
if(!f&&!u)return void console.log("Command is only available in WSL or inside a Visual Studio Code terminal.");const o=Object.assign({},l.OPTIONS),r=u?d:p;for(const e in l.OPTIONS){const t=e;r(t)||delete o[t]}f&&(o.gitCredential={type:"string"});const m={onMultipleValues:(e,t)=>{console.error(`Option ${e} can only be defined once. Using value ${t}.`)},onUnknownOption:t=>{console.error(`Ignoring option ${t}: not supported for ${e.executableName}.`)}},y=l.parseArgs(t,o,m),w=h?A:e=>e;if(y.help)return void console.log(l.buildHelpMessage(e.productName,e.executableName,e.version,o,!0));if(y.version)return void console.log(l.buildVersionMessage(e.version,e.commit));if(y.gitCredential)return void function(e){const t={get:"fill",store:"approve",erase:"reject"}[e];if(void 0===t)return void console.log("Expected get, store or erase.");let n="";process.stdin.setEncoding("utf8"),process.stdin.on("data",e=>{"\n"!==(n+=e)&&-1===n.indexOf("\n\n",n.length-2)||(process.stdin.pause(),b(t,n).catch(console.error))}),
process.stdin.on("end",()=>{b(t,n).catch(console.error)})}(y.gitCredential);let $=(y["folder-uri"]||[]).map(w);y["folder-uri"]=$;let O=(y["file-uri"]||[]).map(w);y["file-uri"]=O;let P=y._,S=!1;for(let e of P)"-"===e?S=!0:x(e,w,$,O);if(y._=[],S&&0===O.length&&0===$.length&&c.hasStdinWithoutTty()){const e=c.getStdinFilePath();try{c.readFromStdin(e,!!y.verbose),x(e,w,$,O),y.wait=!0,y["skip-add-to-recently-opened"]=!0,console.log(`Reading from stdin via: ${e}`)}catch(e){console.log(`Failed to create file to read via stdin: ${e.toString()}`)}}if(y.extensionDevelopmentPath&&(y.extensionDevelopmentPath=y.extensionDevelopmentPath.map(e=>w(C(e).href))),y.extensionTestsPath&&(y.extensionTestsPath=w(C(y.extensionTestsPath).href)),h&&(y.remote=h),u){let e=[];for(let t in y){let n=y[t];if("boolean"==typeof n)n&&e.push("--"+t);else if(Array.isArray(n))for(let o of n)e.push(`--${t}=${o.toString()}`);else n&&e.push(`--${t}=${n.toString()}`)}const t=s.extname(u);if(".bat"===t||".cmd"===t){const t=g||process.cwd()
;y.verbose&&console.log(`Invoking: cmd.exe /C ${u} ${e.join(" ")} in ${t}`),i.spawn("cmd.exe",["/C",u,...e],{stdio:"inherit",cwd:t})}else{const t=s.dirname(u),n=Object.assign(Object.assign({},process.env),{ELECTRON_RUN_AS_NODE:"1"});e.unshift("resources/app/out/cli.js"),y.verbose&&console.log(`Invoking: ${u} ${e.join(" ")} in ${t}`),i.spawn(u,e,{cwd:t,env:n,stdio:["inherit"]})}}else{if(0===t.length)return void console.log(l.buildHelpMessage(e.productName,e.executableName,e.version,o,!0));if(y.status)return void v({type:"status"}).then(e=>{console.log(e)});if(!O.length&&!$.length)return void console.log("At least one file or folder must be provided.");let i=void 0;if(y.wait){if(!O.length)return void console.log("At least one file must be provided to wait for.");i=a.createWaitMarkerFile(y.verbose)}v({type:"open",fileURIs:O,folderURIs:$,diffMode:y.diff,addMode:y.add,gotoLineMode:y.goto,forceReuseWindow:y["reuse-window"],forceNewWindow:y["new-window"],waitMarkerFilePath:i}),i&&async function(e){
for(;n.existsSync(e);)await new Promise(e=>setTimeout(e,1e3))}(i)}}async function b(e,t){const n=await v({type:"command",command:"git.credential",args:[{command:e,stdin:t}]}),{stdout:o,stderr:i,code:r}=JSON.parse(n);o&&process.stdout.write(o),i&&process.stderr.write(i),r&&process.exit(r)}function v(e){return new Promise(t=>{const n=JSON.stringify(e);if(!f)return console.log("Message "+n),void t("");const o={socketPath:f,path:"/",method:"POST"},i=r.request(o,e=>{const n=[];e.setEncoding("utf8"),e.on("data",e=>{n.push(e)}),e.on("error",()=>y("Error in response")),e.on("end",()=>{t(n.join(""))})});i.on("error",()=>y("Error in request")),i.write(n),i.end()})}function y(e){console.error("Unable to connect to VS Code server."),console.error(e),process.exit(1)}t.main=m;const w=process.env.PWD||process.cwd();function C(e){return e=e.trim(),e=s.resolve(w,e),new o.URL("file:///"+e)}function x(e,t,o,i){let r=t(C(e).href);try{n.lstatSync(n.realpathSync(e)).isFile()?i.push(r):o.push(r)}catch(t){
"ENOENT"===t.code?i.push(r):console.log(`Problem accessing file ${e}. Ignoring file`,t)}}function A(e){return e.replace(/^file:\/\//,"vscode-remote://"+h)}let[,,$,O,P,S,...z]=process.argv;m({productName:$,version:O,commit:P,executableName:S},z)}))}).call(this);
//# sourceMappingURL=https://ticino.blob.core.windows.net/sourcemaps/5763d909d5f12fe19f215cbfdd29a91c0fa9208a/core/vs/server/remoteCli.js.map
