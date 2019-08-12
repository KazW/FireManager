<script>
  import { createEventDispatcher } from "svelte";

  export let error = false;
  export let errors = {};
  const dispatch = createEventDispatcher();

  const ok = () => dispatch("ok");
</script>

<div class="modal {error ? 'is-active' : ''}">
  <div class="modal-background" />
  <div class="modal-card">
    <header class="modal-card-head has-background-danger">
      <p class="modal-card-title has-text-light">Please Fix These Errors</p>
    </header>
    <section class="modal-card-body has-text-dark">
      <div class="content">
        {#each Object.entries(errors) as [field, errorMessages]}
          {#if errorMessages.length > 0}
            <h3>{field}</h3>
            <ul>
              {#each errorMessages as errorMessage}
                <li>{errorMessage}</li>
              {/each}
            </ul>
          {/if}
        {/each}
      </div>
    </section>
    <footer class="modal-card-foot">
      <button on:click={ok} class="button is-success" aria-label="ok">
        Ok
      </button>
    </footer>
  </div>
</div>
