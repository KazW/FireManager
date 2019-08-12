<script>
  import { fly } from "svelte/transition";
</script>

<style>

</style>

<div
  in:fly={{ y: -200, duration: 1000 }}
  class="columns is-centered is-vcentered">
  <div class="column is-half">
    <h1 class="title">Monitor</h1>
  </div>
</div>
