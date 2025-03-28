<h1 align="center"><code>roverlib</code> for <code>c</code></h1>
<div align="center">
  <a href="https://github.com/VU-ASE/roverlib-c/releases/latest">Latest release</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://ase.vu.nl/docs/category/roverlib-c">Documentation</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://ase.vu.nl/docs/framework/glossary/roverlib">About the roverlib</a>
  <br />
</div>
<br/>

**When building a service that runs on the Rover and should interface the ASE framework, you will most likely want to use a [roverlib](https://ase.vu.nl/docs/framework/glossary/roverlib). This is the variant for C.**

## Initialize a C service

You can initialize a service with the C roverlib using `roverctl` as follows:

```bash
roverctl service init c --name c-example-service --source github.com/author/example-service-service
```

Read more about using `roverctl` to initialize services [here](https://ase.vu.nl/docs/framework/Software/rover/roverctl/usage#initialize-a-service).


