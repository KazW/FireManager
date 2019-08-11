import Connecting from "../svelte/pages/Connecting.svelte";
import Monitor from "../svelte/pages/Monitor.svelte";
import Settings from "../svelte/pages/Settings.svelte";
import WiFi from "../svelte/pages/WiFi.svelte";

let routes;
const urlParams = new URLSearchParams(window.location.search)
if (!urlParams.has('routemap')) {
  routes = {
    "/": Connecting,

    "/settings": Settings,
    "/monitor": Monitor,
    "/wifi": WiFi,

    "*": Connecting
  }
}
else {
  routes = new Map();

  routes.set('/', Connecting);

  routes.set('/settings', Settings);
  routes.set('/monitor', Monitor);
  routes.set('/wifi', WiFi);

  routes.set('*', Connecting);
};

export default routes;
