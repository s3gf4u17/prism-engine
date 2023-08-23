<h1 align="center">Prism Engine</h1>

<h3>Overview</h3>

Prism is an amateur engine for rendering 3d scenes. I started the project in order to learn more about geometric algorithms. I intend to develop it further in my spare time :D

<h3>Manual</h3>

At the time of writing, there are no pre-compiled releases ready. User needs to clone the repository, change path to obj file in `main.cpp` (line 25) and compile the program manually:

```
git clone https://github.com/s3gf4u17/prism-engine
cd prism-engine
g++ -std=c++11 main.cpp -o prism-engine
sudo mv prism-engine /bin/
```

Note: any obj file can be rendered (in Blender use export -> selected only -> forward axis Y -> up axis Z).

<h3>Results</h3>

<table width="100%">
  <tr>
  <td width="33.3%" align="center">Fragment Shader</td>
  <td width="33.3%" align="center"></td>
  <td width="33.3%" align="center"></td>
  </tr>
  <tr>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/6c25fa51-7de8-4997-9fb3-d330b15b3832"/></td>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/a0c486ba-bcf4-47f8-bca4-bdb0032cec89"/></td>
  <td width="33.3%"></td>
  </tr>
</table>

<table width="100%">
  <tr>
  <td width="33.3%" align="center">Prism 0.2</td>
  <td width="33.3%" align="center">Eevee (Blender)</td>
  <td width="33.3%" align="center">Cycles (Blender)</td>
  </tr>
  <tr>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/3a2bcbeb-88ac-44d5-92c6-399085887d66"/></td>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/b194885e-0ff8-41ea-8703-913d0cc16bef"/></td>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/e05d29d9-bb47-44ee-b8be-d06fee6e93b6"/></td>
  </tr>
</table>

<h3>Changes</h3>

- v 0.2
  - phong normal interpolation

- v 0.1
  - ray casting
  - z buffer
  - diffuse colors
  - single source lighting