<script>
  import { fly } from "svelte/transition";
  import { push } from "svelte-spa-router";
  import { validate } from "../../ts/validators/wifi";

  import ErrorModal from "../ErrorModal.svelte";
  let error;
  let errors;

  let host = "";
  let ssid = "";
  let password = "";
  let saved = false;

  function dismissErrors() {
    error = false;
    errors = {};
  }

  async function validateWiFiSettings() {
    const result = validate(host, ssid, password);
    if (result.error) {
      error = result.error;
      errors = result.errors;
    } else {
      await fetch("__API_URL__/api/wifi", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          Accept: "application/json"
        },
        body: JSON.stringify({ host: host, ssid: ssid, password: password })
      })
        .then(() => {
          console.log("Wifi settings saved!");
          saved = true;
        })
        .catch(err => {
          error = true;
          errors = {
            FireManager: [
              "Unable to contact FireManager, try again, or reset device."
            ]
          };
        });
    }
  }
</script>

<div
  in:fly={{ y: 200, duration: 1000 }}
  class="columns is-centered is-vcentered">
  <div class="column is-half">
    <h1 class="title">WiFi Settings</h1>
    <div class="field">
      <div class="control">
        <input
          class="input"
          type="text"
          bind:value={host}
          placeholder="Device Name"
          required
          pattern="[a-z][a-z0-9_-]*"
          minlength="3"
          maxlength="23" />
      </div>
    </div>

    <div class="field">
      <div class="control">
        <input
          class="input"
          type="text"
          bind:value={ssid}
          placeholder="Network Name (SSID)"
          maxlength="32" />
      </div>
      <p class="help">Leave network name blank if using a hidden network.</p>
    </div>

    <div class="field">
      <div class="control">
        <input
          class="input"
          type="password"
          bind:value={password}
          placeholder="Network Password"
          required
          minlength="8"
          maxlength="64" />
      </div>
    </div>

    <div class="field is-grouped">
      <div class="control">
        <button on:click={validateWiFiSettings} class="button is-success">
          Save WiFi Settings
        </button>
      </div>
      <div class="control">
        <button on:click={() => push('/monitor')} class="button is-warning">
          Skip
        </button>
      </div>
    </div>
  </div>
</div>

<ErrorModal bind:error bind:errors on:ok={dismissErrors} />

<div class="modal {saved ? 'is-active' : ''}">
  <div class="modal-background" />
  <div class="modal-card">
    <header class="modal-card-head has-background-success">
      <p class="modal-card-title has-text-light">WiFi Settings Saved</p>
    </header>
    <section class="modal-card-body has-text-dark">
      <div class="content">
        Please check to see if the FireManager has connected when powered on
        manually (status LED is solid green). If using a Mac, iOS device, Linux
        computer with Bonjour installed, or Windows computer with iTunes
        installed,
        <a href="http://{host}.local/">click here</a>
        . Otherwise, determine the IP of the FireManager and type it into your
        browser. If your router provides local DNS, a URL like http://{host}.home/
        may work.
        <br />
        <br />
        If the Status LED is flashing yellow, the FireManager was not able to
        connect to the WiFi network. Place the switch into the "stand alone"
        position and refresh this page after reconnecting to the FireManager
        WiFi network.
      </div>
    </section>
    <footer class="modal-card-foot" />
  </div>
</div>
