# Scripting for Digital Content Creation
Jon Macey

jmacey@bournemouth.ac.uk

---

## Introduction

- Welcome to Scripting for DCC
- All the resources you need will be on this website

https://nccastaff.bournemouth.ac.uk/jmacey/sfdcc/

- Links are on BrightSpace

--

## Aims

> The purpose of this optional unit is to ensure that students are equipped with the programming and scripting skills necessary to use modern Digital Content Creation (DCC) tools such as Maya, Houdini and Nuke.
> Using a “test driven design” (TDD) approach students will learn core software engineering and programming skill to help understand and utilize the architecture of modern DCC tools in the development of pipeline tools and techniques.


--

## Intended learning outcomes (ILOs)

1. understand and apply Test Driven Development / Design to a chosen software development project. 

2. demonstrate an understanding of the architecture and techniques used by digital content creation tools and pipelines. 

3. select, apply and evaluate the correct programming / scripting language and development approach to solve a chosen problem. 

4. apply principles of HCI in the design and production of graphical user interfaces. 


--

## Assessment

- This unit is assessed by a project worth 100% of the unit grade.
- Due in 12 noon 
- Brief is on BrightSpace and we will go over it in the Lab session

---

## Course Overview

- Introduction to Linux / Unix
- Test Driven Development / Design
- Data and the Structure of DCCs
- Python and Production API's
- Problem Solving / Documentation
- GUI's and HCI (PyQt / PySide)
- Databases / SQL
- And much more!

---

# [Roles](https://www.screenskills.com/media/3232/animation-map-web-2019.pdf) 

<img style="border: 0;" src="images/jobs.png" width="80%">

---

# Why Scripting?

- All DCC tools are now scriptable, we can use it to automate the boring stuff
- We can use it to make our own tools
- customize the UI / make it easier to use
- Python is generally easier to use / setup than other languages (C++ for example)

--

## A (brief) History of DCC programming

- Very early days of computer animation used analog computers
- Not until the 80's that digital computers we used
  - Whilst this was the beginning of home computers most computers were [mini / mainframes](https://en.wikipedia.org/wiki/VAX) in an academic environment.
- Mainly running a Unix like OS

--

## Early Animation Systems

- Early animation systems were usually small programs piped together
  - intermediate representations fed into the pipeline to generate input for renderer
  - Standard Unix tools used to modify (sed / awk)
- Most programs written in C 

--

## No off the shelf 1990's

- There were no off the shelf tools so most were developed in house 
  - NCCA had it's own CGAL (needed to program to use)
- Power Animator was the Industry standard but needed IRIX / SGI machines and £7K a seat!

--

## Coding Animation
<div id="mySlideLeftCode">
<iframe src="sphere.html" ></iframe>
</div>
<div id="mySlideRightCode">
```
SCRIPT 1 TO 150 DO
  BEGIN
    FROM 1 TO 100 EVERY 25 LOOP 10 DO
      RZ [ball] 1.5;
      .....
  END;
```
</div>
- This generates 150 frames of animation 
  - makes the object ```[ball]``` rotate around the z axis by 1.5 degrees in loops of 10 frames every 25 
  - i.e. 1-10  26-35 51-60 76-85

--

## Enter the tools

- via various mergers animation tools began to appear
- Early tools started to be packaged into GUI systems 
  - but the underlying systems are still scripts 
- Most GUI tools are just glued together with scripts

--

## Scripting Languages

- MEL (Maya Embedded Language) based on [Perl](https://www.perl.org/) and [TCL](https://www.tcl.tk/about/language.html)
- HScript Houdini scripting language
- XSI used Python, Perl, JavaScript and VB Script
- Python started in Maya 8.5 
- [Lua](https://www.lua.org/) quite common in pipelines and bespoke tools

--

# Python

- Python is now the main language used in DCC tools, this is due to the way (C)Python allows easy embedding of existing API's into new modules
  - This process is beyond the scope of these lectures as requires C/C++ knowledge but more [here](https://nccastaff.bournemouth.ac.uk/jmacey/Lectures/PTD/L3/?home=/jmacey/msc/PipeLineAndTD#/3)
- One thing to note is each DCC will ship with their own version of python which can make things complex. 
- The VFX reference platform dictates what version https://vfxplatform.com/

--

## Python

- Typically python is used to glue together other tools
- It can be the main language for a tool or pipeline
- But what exactly is this "mythical" pipeline we hear so much about?

---



# What is a Pipeline?

- At it's simplest level it can be split into 3 elements
  1. Pre-Production
  2. Production 
  3. Post-Production

- This is similar for most productions such as Full CG, VFX and to some extent games.
- Slightly different for Virtual Production

--

# Pre-Production

- Script / Story development
- Production design
- Concept Art / Design Bible
- Storyboarding
- Animatics

--

# Pre-Production

- predominantly an artistic role.
- still lots of data
  - can also be physical assets which may need to be digitized.
- This will feed into next production stage and data needs to be accessible to all

--

# Production 

- This is the main area for pipeline, there are lots of sub elements but a simple taxonomy is as follows
- 3D Layout
- 3D Modeling
- VFX
- Match move / Tracking  if using live plates
- Lighting
- Rendering

--

# Production

- Some of the previous elements can be concurrent
  - for example layout can use proxy models until final ones are complete
- Some sub elements within the groups have to be sequential

--

# 3D Modelling

- This can be split into many parts
  - Basic Mesh / Model creation
  - Texturing (including sculpt)
  - UV Layout
  - Rigging
  - Animation
- Lots of data and versions. Needs careful management and control

--

# VFX / Simulation

- VFX / Simulation can be time consuming
- Big sims take time and data may need to be cached
- If dependant on other elements they need to wait (destroy buildings etc)
- may need to work alongside the animators and modelers due to interaction with colliding FX elements

--

# Lighting / Rendering

- Another time consuming process
- Need other elements in place before doing renders
- Need to ensure we get all the passes / AOV's required
- IBL may be used so could have large input data too
- Large amount of data to manage / pass onto compositors

--

# Post-production

- Can be split into
  - Compositing 
  - 2D Effects ( lens flares, blurs, camera shakes, rain)
  - Colour correction / grade
- Final render to destination format

--

# Virtual Production

- moves tasks such as rendering, lighting, matchmove, camera tracking, into the production process
- On Set / Soundstage LED projection used to capture elements in camera
- Still needs other element and post processing
- Can also add 'physical computing' elements

---

# What is a Pipeline?

- A collection of rules and tools that facilitates groups of people to work collaboratively on large-scale projects.

- There can be many departments, groups and people working in the pipeline
  - They may be spread all over the world

--

# <small>What are the features of a Pipeline</small>

- Broad groups of users should be defined : Coordinators, Animators, Modellers, Compositors etc
- Producers want to keep track of all progress on a show/shot
- All artists should be able to start working on a shot as soon as possible
- Changes to assets can be made at any time, causing as few problems to artists ‘downstream’ as possible
- All assets are versioned

--

# We need standards

- Naming conventions are a must.
- An explicit understanding of downstream’s concerns
  -  we need an Alert system when something goes wrong (send upstream?)
- Common methods / formats / tools
- These can be a per company or per show set of rules
- Very common for multiple companies to now work on a show.

--

# A filing system

- A directory structure repeated from show to show, sequence to sequence, shot to shot
- As we may use many DCC tools this may change to suite the tool
- Or can be a custom one
  - Maya and Houdini have their own project setups so we need to adapt to this.

--

# A filing system

- Using a rigid filing-system means we can use a database to track assets
- Many tools will exist to create and maintain the filing system (usually command-line scripts)
- Disk space always of concern so needs to be managed
- Tools like Shotgun / Shotgrid can help with some of the tracking
- Traditional software version control does not work well with assets

--

# What is an Asset?

- Assets are a product of all departments/users 
  - Producers will monitor asset progress and assign users/artists to the creation of assets.
- Most things artists make are assets :
  - Scenefiles, models, uv maps, textures, animation, textures, shaders, particles, light-rigs, etc.
- Management of this data is core to all pipelines, can be Terra bytes or more

--

# Dependency chains

- Assets can form dependency chains
  - User Dependencies :
    -  Rigger is dependent on the Modeler
  - Asset Dependencies :
    - this version of the animation is dependent on the model (version 2) and the creature-rigging (version 3)
- Yet another complex part of the pipeline, database helps to manage this
- check in / out of assets crucial

--

# <small> Dependency Accumulation </small>

- Dependencies accumulate as you travel along the pipeline.
- Just one simple animated asset could have :
  - Model, uv map, rigging, enveloping,  animation, textures, shaders

--

# Database tracking

- as the dependencies accumulate we can use a database to track things
  - very handy to see if upstream assets have been updated and allow new versions to be checked out
- can be coupled with a the filing system to allow easy updates. 
- This is usually done via extra metadata / alert system in our tools


--

# <small> Publishing / Quarantine </small> 

- Once an artist has produced an asset, that asset might need to be published so that the other users downstream can start to use it
- All assets are quarantined prior to achieving a full publish
- A quarantined asset can be upgraded to full publish once each group downstream has verified its quality (Department leads)

---

# <small>Case Study Publishing a Model </small>

- A model is ready to be published 
- Either manually or (preferably) using the pipeline tools we need to
  -  The model scene is cleaned of all non-essentials (no materials, lights, extra node-hierarchies etc)
  -  The model is checked for quality
     -  checked for illegal verts, edges and faces etc
  -  The naming convention is enforced 
- Asset could be published in a standard format (Obj, FBX, USD etc)

--

# Publishing

- Once the previous steps are complete the model can be published
- Usually a tool is used to publish
  - All downstream users of the asset need to be alerted
- Usually some form of Metadata is filled in with the details (json asset files for example)
- This can be controlled via our database or file system and the new asset replaces the old one
- Could be as simple as a directory change

--

# Problems can occur

- Any changes made since the last publish, may cause issues downstream 
- Have the number of vertices changed?
  - This would affect uv-maps (and thus texturing/shaders)
  - This would affect enveloping.

- Has the uv-map been altered?
  - This can affect TD’s particle sims.
  - Occlusion may have to be re-baked

--

# The role of pipeline

- A good pipeline should make changes easy
- Allowing different teams to work both together and in isolation
  - If a modeler updates a model asset, the asset shouldn’t be inserted into scenes downstream automatically
  - Downstream users should be able to update their scenes, when they’re ready, with relative ease

--

# DCC Tools

- Most DCC tools asset management tools are not good. 
  - whilst fine for a simple user or single DCC house can work ok, don't scale well to big productions
- Most big teams use their own / 3rd party tools
- A 'pull' pipeline where the DCC pulls in data based on meta data / schemas

---

# Sample Schema 

- We can generate simple schemas for a shot
- Usually simple text or json (ASCII) or could be python script to query database etc
- A description of what the shot needs (creatures, props, cameras, resolution, etc)
- Each user has their own shotfile and sometimes use multiple shot files within one shot.

--

# [USD](https://graphics.pixar.com/usd/release/index.html)

- Many companies are moving to USD based pipeline or integrating USD within existing pipelines
- USD provides for interchange of elemental assets (e.g. models) or animations 
- But unlike other interchange packages, USD also enables assembly and organization of any number of assets into virtual sets, scenes, shots, and worlds, transmitting them from application to application
- We will look at this later in this unit


---

## References and Links

- https://www.vegascreativesoftware.com/gb/post-production/3d-animation-pipeline-for-efficient-animation-production/

- http://www.pipelinepatterns.com/intro/welcome.html
- https://www.cgspectrum.com/blog/the-visual-effects-pipeline