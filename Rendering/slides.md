## Introduction to Rendering

`$$ L_{\text{o}}(\mathbf x,\, \omega_{\text{o}},\, \lambda,\, t) \,=\, $$`
` $$L_e(\mathbf x,\, \omega_{\text{o}},\, \lambda,\, t) \ +\, \int_\Omega f_r(\mathbf x,\, \omega_{\text{i}},\, \omega_{\text{o}},\, \lambda,\, t)\, L_{\text{i}}(\mathbf x,\, \omega_{\text{i}},\, \lambda,\, t)\, (\omega_{\text{i}}\,\cdot\,\mathbf n)\, \operatorname d \omega_{\text{i}} $$`


Jon Macey

jmacey@bournemouth.ac.uk



---

## Why all the Maths?

- Don't worry this is not going to be a maths lesson
  - however every time you render that equation (or similar) is being executed
  - for every pixel!
  - your doing maths without even knowing it.

--

## Why all the Maths?

- With a little work we are going to break the equation down into sections which explain what they are doing.
- [we will use diagrams not formula](https://en.wikipedia.org/wiki/Rendering_equation)

![brdf](images/eq1.png)


--

## We will also cover some Physics

> In physics and chemistry, the law of conservation of energy states that the total energy of an isolated system remains constant; it is said to be conserved over time. This law means that energy can neither be created nor destroyed; rather, it can only be transformed or transferred from one form to another.
[source](https://en.wikipedia.org/wiki/Conservation_of_energy)

--

## We will also cover some Physics

<blockquote/><small/><p/>Energy Conservation plays a vital role in physically-based rendering solutions. It states that the total amount of light re-emitted by a surface (reflected and scattered back) is less than the total amount it received. In other words, the light reflected off the surface will never be more intense than it was before it hit the surface. As artists, we don't have to worry about controlling Energy Conservation. This is one of the nice aspects of PBR in that energy conservation is always enforced by the shader. It’s part of the physically-based model and it allows us to focus more on art rather than physics.
[PBR Guide Vol 1](https://www.substance3d.com/system/files/software/download/build/PBR_Guide_Vol.1.pdf)



---




## A brief history or rendering

> As technology advances, rendering time remains constant.
  — [Blinn’s Law](http://boxxblogs.blogspot.com/2013/07/blinns-law-and-paradox-of-increasing.html)

- Early computer graphics research started in the 1970's however some of the foundations go back even earlier.

- Many of the principles used then are still relevant today we've just increased the complexity of what we are simulating
- Hence the truism of Blinn's Law.


--

## 1950's - 1960's
- [Ray Tracing / Casting by Arthur Appel 1968](http://people.reed.edu/~jimfix/math385/lec01.1/Light/Appel.pdf)
- CRT displays (not colour)
- [SketchPad](https://en.wikipedia.org/wiki/Sketchpad)

<iframe width="560" height="315" src="https://www.youtube.com/embed/495nCzxM9PI" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

--

## 1970's

- University of Utah computer group
- Hidden surface determination
- Shading  Henri Gouraud, Jim Blinn and Bui Tuong Phong
  - Textures, Environment Maps, Bump mapping :- Jim Blinn
- Z buffer and Alpha 
- Recursive ray tracing algorithm [Turner Whitted  1979](https://blogs.nvidia.com/blog/2018/08/01/ray-tracing-global-illumination-turner-whitted/) 


--

## 1980's
- Ray tracing improvements

<iframe width="560" height="315" src="https://www.youtube.com/embed/0KrCh5qD9Ho" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

- Pixar start to develop Shaders / Shading Languages
- Introduction of real time graphics boards (first GPU's)


--

## 1990's

- Toy Story 
- Beginnings of photorealism in CGI
- Normal Mapping
- Better GPU's
- Introduction of Physically Based Models ()

--

## 2000's till now
- more access to texture maps 
- HDRI
- Real Time Ray-tracing on consumer hardware
- [Physically Based Rendering](http://www.pbr-book.org/3ed-2018/Introduction/A_Brief_History_of_Physically_Based_Rendering.html) 



---

## Raytracing

<img src="https://upload.wikimedia.org/wikipedia/commons/8/83/Ray_trace_diagram.svg" width="80%">

<p><small><a href="https://commons.wikimedia.org/wiki/File:Ray_trace_diagram.svg">image source</a></small></p>

--

## How about some Code!

```
for (int j = 0; j < imageHeight; ++j) { 
    for (int i = 0; i < imageWidth; ++i) { 
        // compute primary ray direction
        Ray primRay; 
        computePrimRay(i, j, &primRay); 
        // shoot prim ray in the scene and search for intersection
        Point pHit; 
        Normal nHit; 
        float minDist = INFINITY; 
        Object object = NULL; 
        for (int k = 0; k < objects.size(); ++k) { 
            if (Intersect(objects[k], primRay, &pHit, &nHit)) { 
                float distance = Distance(eyePosition, pHit); 
                if (distance < minDistance) { 
                    object = objects[k]; 
                    minDistance = distance; // update min distance 
                } 
            } 
        } 
        if (object != NULL) { 
            // compute illumination
            Ray shadowRay; 
            shadowRay.direction = lightPosition - pHit; 
            bool isShadow = false; 
            for (int k = 0; k < objects.size(); ++k) { 
                if (Intersect(objects[k], shadowRay)) { 
                    isInShadow = true; 
                    break; 
                } 
            } 
        } 
        if (!isInShadow) 
            pixels[i][j] = object->color * light.brightness; 
        else 
            pixels[i][j] = 0; 
    } 
} 
```

<p><small><a href="https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/implementing-the-raytracing-algorithm">source</a></small></p>

--

## Raytracing


<blockquote><small><p>Almost all photorealistic rendering systems are based on the ray-tracing algorithm. Ray tracing is actually a very simple algorithm; it is based on following the path of a ray of light through a scene as it interacts with and bounces off objects in an environment. Although there are many ways to write a ray tracer, all such systems simulate at least the following objects and phenomena [PBR Book](http://www.pbr-book.org/3ed-2018/Introduction/Photorealistic_Rendering_and_the_Ray-Tracing_Algorithm.html)</p></small></blockquote>


- Cameras
- Ray–object intersections
- Light sources
- Visibility
- Surface scattering
- Indirect light transport
- Ray propagation

--

## Cameras

![](http://www.pbr-book.org/3ed-2018/Introduction/Pinhole%20Camera.svg)
[source](http://www.pbr-book.org/3ed-2018/Introduction/Photorealistic_Rendering_and_the_Ray-Tracing_Algorithm.html)
- The simplest model of a camera is the ["pinhole camera"](https://en.wikipedia.org/wiki/Pinhole_camera)
- The generally need long exposures when using film, be in CGI can make things a lot simpler.

--

## Cameras
<img src="http://www.pbr-book.org/3ed-2018/Introduction/Film%20in%20front.svg" width="40%">
- When we simulate pinhole cameras we place the film in the front of the hole at the near plane, the hole is then called the "eye"
- We can then add other transformations to simulate, projections and lenses.

--

## Ray–object intersections

- Each time the camera generates a ray, the renderer must determine which object, if any, the ray intersects first and where the intersection occurs.
- This intersection point is the visible point along the ray, and we then simulate the interaction of light with the object at this point.
- To find the intersection, we must test the ray for intersection against all objects in the scene and select the one that the ray intersects first.
- There is a relationship between the image size, number of objects and ray count with respect to render time.


--

## Light sources

- we need to find the amount of light leaving this point in the direction of the camera.
- so we need to know how much light is arriving at this point. 
- This involves both the geometric and radiometric distribution of light in the scene. 
- Whilst point and spot light sources are common in CGI tools they are not really that good for PBR systems
- Tend to use area light sources.

--

## Visibility

-  Each light contributes illumination to the point being shaded only if the path from the point to the lights position is unobstructed

<img src="http://www.pbr-book.org/3ed-2018/Introduction/Two%20lights%20one%20blocker.svg" width="40%">


--

## Surface Scattering
<img src="http://www.pbr-book.org/3ed-2018/Introduction/Surface%20scattering%20geometry.svg" width="40%">

- Now we need to determine how the incident lighting is scattered at the surface. 
- Specifically, we are interested in the amount of light energy scattered back along the ray that we originally traced to find the intersection point, since that ray leads to the camera

--

## Surface Scattering

- Each object in the scene provides a material, which is a description of its appearance properties at each point on the surface. 
- This description is given by the bidirectional reflectance distribution function (BRDF).

```
for each light:
    if light is not blocked:
        incident_light = light.L(point)
        amount_reflected = 
            surface.BRDF(hit_point, camera_vector, light_vector)
        L += amount_reflected * incident_light
```

--

## Indirect light transport

<img src="http://www.pbr-book.org/3ed-2018/Introduction/Ray%20Tree.svg" width="40%">

<blockquote><small><p>Turner Whitted’s original paper on ray tracing (1980) emphasized its recursive nature, which was the key that made it possible to include indirect specular reflection and transmission in rendered images.</p></small></blockquote>


--

## Ray propagation

- So far we have assumed the rays are traveling in a vacuum. 
- There are two ways in which a participating medium can affect the light propagating along a ray. 
  - the medium can extinguish (or attenuate) light, either by absorbing it or by scattering it in a different direction
  - medium can also add to the light along a ray. This can happen either if the medium emits light (as with a flame) or if the medium scatters light from other directions back along the ray.

--



## Ray propagation

- This is usually generated by adding a Volume to the scene
<img src="images/novolume.png" width="50%"><img src="images/volume.png" width="50%">

---

## Theory of Light

<iframe width="1024" height="800" src="lights.html"></iframe>


--

## Theory of Light

- Light is technically an electromagnetic transverse wave, which means that the electromagnetic field wiggles sideways as the energy propagates forwards. 
- This wiggling in the electromagnetic field can be seen as two coupled fields, electric and magnetic, wiggling at 90 degrees to each other.
- The closest we get to this in the real world is a Laser.

--

## Frequency of Light

<p/><img src="images/light.png" alt="light" width="50%">

--

## Some Scale

<img src="images/hair.png" width="100%">

--


## Theory of Light

- Most light waves contain many different wavelengths, with a different amount of energy in each. 
- This is know as the Spectral power distribution (SPD)

<img src="images/SPD.png" width="80%">


--

## Theory of Light


<div class="stretch">
<iframe width="900" height="90%" src="add.html"></iframe>
</div>

--



# Watch this

<iframe width="560" height="315" src="https://www.youtube.com/embed/j-A0mwsJRmk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


---



## BRDF

---

## PBR in Practice

---

## Tools and Support

---


## References
- http://www.pbr-book.org/3ed-2018/contents.html
- https://www.chaosgroup.com/blog/understanding-metalness
- https://blog.selfshadow.com/publications/s2015-shading-course/hoffman/s2015_pbs_physics_math_slides.pdf
