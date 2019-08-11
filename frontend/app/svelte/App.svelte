<script>
  import Router from "svelte-spa-router";
  import "../css/main.scss";
  export let routes;
</script>

<section class="hero is-dark is-fullheight">
  <div class="hero-body">
    <div class="container">
      <Router {routes} />
    </div>
  </div>
</section>
