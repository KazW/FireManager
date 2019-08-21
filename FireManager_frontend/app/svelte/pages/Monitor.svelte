<script>
  import { onMount } from "svelte";
  import { fly } from "svelte/transition";

  let temperature = 0;
  let setPoint = 0;
  let blowerLevel = 0;

  onMount(() => {
    if ("WebSocket" in window) {
      let socket = new WebSocket(
        "ws://" + window.location.hostname + "/sockets"
      );
      socket.onmessage = function(evt) {
        let update = JSON.parse(evt.data);
        temperature = update.temperature;
        setPoint = update.setPoint;
        blowerLevel = update.blowerLevel;
      };

      return () => {
        socket.close();
      };
    } else {
      const interval = setInterval(async () => {
        const res = await fetch("__API_URL__/api/status");
        let status = await res.json();

        temperature = status.temperature;
        setPoint = status.setPoint;
        blowerLevel = status.blowerLevel;
      }, 1000);

      return () => {
        clearInterval(interval);
      };
    }
  });
</script>

<style>

</style>

<div
  in:fly={{ y: -200, duration: 1000 }}
  class="columns is-centered is-vcentered">
  <div class="column is-half">
    <h1 class="title is-1">Monitor</h1>
    <p class="subtitle">Temperature: {temperature}&deg;F</p>
    <p class="subtitle">Set Point: {setPoint}</p>
    <p class="subtitle">Blower Level: {blowerLevel}</p>
  </div>
</div>
