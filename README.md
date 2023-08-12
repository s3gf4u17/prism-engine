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
  <td width="33.3%" align="center">Prism 0.2</td>
  <td width="33.3%" align="center">Eevee (Blender)</td>
  <td width="33.3%" align="center">Cycles (Blender)</td>
  </tr>
  <tr>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/0bbaa507-0e0b-46eb-9e3d-5ddd98ca0b7a"/></td>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/d5f8f48a-2d05-4e29-8af5-a30eb2ef2b71"/></td>
  <td width="33.3%"><img src="https://github.com/s3gf4u17/prism-engine/assets/86662946/2717c9c9-87c7-422d-aa78-4cce89c95cdc"/></td>
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