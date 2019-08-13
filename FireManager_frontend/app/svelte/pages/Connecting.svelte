<script>
  import { onMount } from "svelte";
  import { replace } from "svelte-spa-router";

  onMount(async () => {
    const res = await fetch("__API_URL__/api/status");
    let config = await res.json();

    if (config.wifiClient) {
      replace("/monitor");
    } else {
      replace("/wifi");
    }
  });
</script>

<div class="columns is-centered is-vcentered">
  <div class="column is-half">
    <h1 class="title">Connecting to FireManager...</h1>
    <h2 class="subtitle">
      <progress class="progress is-success" max="100">30%</progress>
    </h2>
  </div>
</div>
