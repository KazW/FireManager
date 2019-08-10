<script>
  import "../css/main.scss";
  import { Button } from "svelma";
  import { Icon } from "svelma";
  export let name;
</script>

<style>
  h1 {
    color: purple;
  }
</style>

<h1>Hello {name}!</h1>
<Button type="primary">I'm a Button!</Button>
<Icon pack="fab" size="is-large" icon="github" />
<Icon pack="fas" size="is-large" icon="download" />
<Icon pack="far" size="is-large" icon="angry" />
