## Pipeline and Technical Direction
## Lecture 2 DCC Data structures
Jon Macey

jmacey@bournemouth.ac.uk

---

## Introduction

- In this lecture we will look at _some_ of the data structures used in DCC tools
- We will determine some of architectural patterns used (Graphs etc)
- We will discuss formats and structure for data

--

# Motivation

- The main reason to look at this is to help us understand how data is formatted so we can process it
- This helps with pipelines and data transfer
- Gives us an understanding of the design / API's of the DCC Tools 
- Will mainly focus on Maya and Houdini (with some mention of other tools)

---

# A DCC as a data filter

- At it's simplest level we could see most DCC tools as a simple Input -> Process -> Output [IPO](https://en.wikipedia.org/wiki/IPO_model) model.
  - These are usually represented as Nodes in a bigger Graph
- A lot of this goes back to the early days of the tools (80's and 90's)

--

# [Before Houdini](https://www.youtube.com/watch?v=2YXwg0n9e7E&t=4s&ab_channel=CppCon)

![](images/Hou1.png)

--

# [Before Houdini](https://www.youtube.com/watch?v=2YXwg0n9e7E&t=4s&ab_channel=CppCon)

- Artist used discrete tools piped into each other
- Makefiles where then use to build pipelines
- Tools like [sed](https://www.gnu.org/software/sed/manual/sed.html) and [awk](https://www.gnu.org/software/gawk/manual/gawk.html) were used to change params per frame
- Most early production pipelines were like this (and under Unix systems)
- These ideas are still prevalent in DCC tools, now just using GUI's instead.

--

# A Procedural Approach

![](images/ipo.png)
- Nodes are basically procedures
  - Can use encapsulation to hide other procedures
- Attributes are set for the process and usually apply to all inputs
- This allows the data to be processed in a SIMD fashion


---

## A Taxonomy of Parallel Machines

- Earliest parallel machines were developed in the 60's
- In 1966 [Michael Flynn](https://en.wikipedia.org/wiki/Flynn%27s_taxonomy) introduced a taxonomy of computer architectures where by machines are classified based on how many data items they can process concurrently.

--

## Single Instruction, Single Data (SISD)
- A simple sequential machine that executes one instruction at a time.
- Most modern CPU's don't work in this way
  - it is now more common that even micro-controllers have multiple cores.
- Each individual core is still a SISD system. 

--

## Single Instruction, Multiple Data (SIMD)
- A machine in which each instruction is applied on a collection of items (data).
- [Vector processors](https://en.wikipedia.org/wiki/Vector_processor) were the very first machines that followed this paradigm.
- GPU's also follow this design at the level of the [streaming multi-processor](https://en.wikipedia.org/wiki/Stream_processing). 
- nVidia and AMD both use these but with different names (SM vs SIMD)

--

## Multiple Instructions, Single Data (MISD)
- This configuration seems like an oddity.
- How can multiple instructions be applied to the same data item?
- If fault tolerance is required (i.e. military, industrial processing etc.) data is processed and pooled to gain a consensus (majority principle).

--

## Multiple Instructions, Multiple Data (MIMD)
- This is the most versatile machine category.
- Multi-core machines including GPU's follow this paradigm.
- GPU's are made from a collection of SM/SIMD units, whereby each can execute its own program.
- Collectively they act as MIDM machines.

--


## Modern refinements
<image src="images/flyn.png" width=60%>
- The taxonomy has been refined of the years with added sub categories.
- In particular MIMD can be defined with either Shared or Distributed memory

--

## Shared Memory MIMD
- has universally accessible shared memory space.
- This simplifies transactions that need to take place between CPUs with minimum overhead, but is a bottleneck to scalability.
- Some systems partition memory so each CPU has it's own memory and (slower) access to the non-local memory of other CPUs.
- This is know as Non-Uniform Memory Access ([NUMA](https://en.wikipedia.org/wiki/Non-uniform_memory_access))

--

## Distributed Memory MIMD
- sometime know as "shared nothing MIMD" 
- are machines that communicate by exchanging messages.
- such machines scale well but have a high communication cost.

--

## Current Trends
- Increase the on-chip core count.
  - Addition of new SIMD instruction sets ([SSE](https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions), [MMX](https://en.wikipedia.org/wiki/MMX_(instruction_set), [AVE](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions) [AESNI](https://en.wikipedia.org/wiki/AES_instruction_set))
  - Larger caches.
- Combine heterogeneous cores in the same package, typically CPU and GPU ones.
  - optimized for a different type of task. 
  - AMD's APU ([Accelerated Processing Unit](https://en.wikipedia.org/wiki/AMD_Accelerated_Processing_Unit)) chips. 
  - Intel is also offering OpenCL-based computing on its line of CPUs with integrated graphics chips.

---

# Why does this matter

- Making use of SIMD means we need to layout data in particular ways
- Usually we use SOA formats (Structure of Arrays)
- Internally most DCC's use variants of this
  - They will have their own containers to utilise this data format
- Also influences how the API's (C++ / Python) work and interface with the tools
  - See ```MVectorArray``` (Maya) ```UT_Array``` (Houdini) etc

--

# What no stl:: ?

- stl proposed in 1994 added in 1998
  - Most DCC tools predate this so had their own
- Also allows for internal structures to be optimized
- Usually Array types and other containers
- Strings can also be problematic so optimized

--

## Custom Memory allocation

- internally most DCC will manage memory allocation and layout
  - Either using external tools [jemalloc](https://github.com/jemalloc/jemalloc) or [tbb malloc](https://github.com/oneapi-src/oneTBB)
- Will use page allocation to save on copies down trees

--

# COW
- [Copy on Write](https://en.wikipedia.org/wiki/Copy-on-write) used to save memory
  - DCC's can  move GB's of data around so we try to avoid copies
- Page allocation helps as we can decide what to copy and what to share
- Obvious overhead in code complexity but save memory
  - Usually transparent to the user


---

# DCC structures

- It can be useful to think of most DCC tools having different levels of structures
  - High Level
    - Scene / Pipeline etc
  - Low Level 
    - Geometry + Metadata etc
- State (Undo / Redo is important with Maya API coding for example)

--

# DCC structures

- Most modern DCC tools are node based (Maya Houdin Nuke)
- This is either hidden or part of the workflow (Maya vs Houdini / Nuke)
- Some tools use a more Functional approach (Katana)
- In most cases we have some form of Graph to be evaluated

---

# Maya Graphs

- [Direct Acyclic Graph](https://en.wikipedia.org/wiki/Directed_acyclic_graph)  or DAG object 
  - Any object that can be parented to another object, and can have children parented to it
- DG  [Dependency Graph](https://en.wikipedia.org/wiki/Dependency_graph)
  - Nodes connected together to create an "output"

--

# DAG 

- There are some simple rules with DAG objects :
  - An object can only have one parent at a time.
  - An object cannot be the child of one of own it’s children. 
- DAG is mostly for hierarchial distinctions. 
- Any node which has transform attributes is a DAG object. 
- You can see DAG nodes when the Hypergraph is in the Scene Hierarchy mode.

--

# [Dependency Graph ](https://patents.google.com/patent/US5929864A/en)

- Allows the flow of node data and attributes
Two main important things here, nodes and their attributes. 
  - connect multiple nodes to come up with an output (rendred images, animated geometry, etc.), 
- These connections are basically the scene (with some extra data)
  - this could be serialized to create a new format etc. 

--

# Dependency Graph 

- A DG node is any node that can be connected to other nodes, and they are not necessarily visible in the Scene Hierarchy mode of the Hypergraph
- you can show the Dependency Graph of a particular object by selecting it and clicking the Input and Output Connections mode.

--

# Dependency Graph 

- Nodes have no control over updates (done in a push-pull fashion form Maya request)
- Dirty bit (flag) is used to propagate the need to update via the outputs (the push)
- Maya updates cause data to be pulled to the input nodes (via DataBlocks)

---

# Houdini

- At it's simplest level houdini is a spreadsheet
  - Data within this sheet are the contents feeding the nodes
  - Can be paths to nodes or other geo
  - Attribute Wrangle can add column to spreadsheet
- Can sort of be seen in the .hip file

--

# Houdini Graphs

- Normally, Houdini processes the nodes in a geometry network from top to bottom, feeding the output of each node into the input of the next node
  - Loops were recently introduced to allow more processing
  
<image src="images/HouEval.png" width=40%>

--

# Cooking

- Nodes are evaluated in houdini via cooking (this will resolve the nodes / orders)

<image src="images/cook.png" width=25%>


---

# Low level structures

- most DCC tools store Geo / Mesh data using arrays with index values
  - Vertex data usually float or double
  - Index 32 / 64 bit index values
- Metadata can be added
- Animation data usually values per channel

--

# Nodes

- Most systems use Nodes with connections
  - Many systems use [UUID](https://en.wikipedia.org/wiki/Universally_unique_identifier) to name nodes
  - ```974967AA-DE42-7E05-3670-3DAFB96967A5``` can use ```uuidgen``` or other libraries

--

## Acessibility patterns


![](images/Hou2.png)


--

## DCC High level differences

- Houdini has native points (very powerful and core to almost everyting)
  - Points can add attributes (```@P``` ```@pscale``` etc)
- Maya has many low level primitives all of which can represent points.
  - vertices, curve cv's, particles, lattice points, cluster handles, subdiv points etc
  - However as different all have different functions  / function sets
- In Houdini, if its a point, it can be manipulated as a point, regardless of how it was created

--

## Houdini Points

<image src="images/HouPoints.png" width=100%>

--

## Houdini Points

```
node = hou.pwd()
geo = node.geometry()
from random import *

def randP(v=1) :
    return (uniform(-v,v),uniform(-v,v),uniform(-v,v))

p=[]

for i in range(0,20) :
    p.append(randP(5))

geo.createPoints(p)
# adds to the geo spreadsheet
geo.addAttrib(hou.attribType.Point, "Cd", (1.0, 1.0, 1.0))
geo.addAttrib(hou.attribType.Point, "pscale", (2.0))
geo.addAttrib(hou.attribType.Point, 'bogus' , 1)    
# now modify the attributes for all bogus field.
for point in geo.points():
    point.setAttribValue('bogus', randint(0,100))
```

--

## Maya Points

- It is not easy to replicate the previous example in Maya
  - Part of pipeline is choosing the right tool for the job!
- Maya doesn't treat points as first class primitives like Houdini
- Can do some of this using [```nParticles```](https://download.autodesk.com/us/maya/2011help/CommandsPython/nParticle.html)

```
from random import uniform
def randP(v=1) :
    return (uniform(-v,v),uniform(-v,v),uniform(-v,v))
p=[]
for i in range(0,20) :
    p.append(randP(5))    
cmds.nParticle( p=p )
```

--

## Meshes 

- in Houdini connecting points creates a primitive
  - These can have attributes as well as the points (but shared per prim)
- SOA format in Houdini. 

<image src="images/HouPrim.png" width=100%>

--

## Simple Mesh Formats

- Most mesh formats have lists of values (verts / points) is the minimum
  - Faces are generated as index values into these lists
- Obj format is one of the simplest and serves as a good starting point

--

## The Obj File format

- Alias Wavefront obj files define the geometry and other properties for objects which can be easily used within animation packages. 
- Object files can be in ASCII format .obj or binary format .mod. 
- For simplicity the ASCII format will be discussed here as it is easier to parse the data and is a good exercise for file and string handling. 
- In its current release, the .obj file format supports both polygonal objects and free-form objects such as curves, nurbs etc.

--

## File Format

- The following types of data may be included in an .obj file. In this list, the keyword (in parentheses) follows the data type.

  - geometric vertices (v)
  - texture vertices (vt)
  - vertex normals (vn)
  - face (f)

--

## File Format
- group name (g)
- smoothing group (s)
- material name (usemtl)
- material library (mtllib)
- all values are stored on a single line terminated with a \n (new line character)

--

## Face Format

- A valid vertex index matches the corresponding vertex elements of a previously defined vertex list.

```
f v1 v2 v3 ....
f v1/vt1 v2/vt2 v3/vt3 ...
f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
f v1//vn1 v2//vn2 v3//vn3 ...
```
- It is also possible to reference points using negative indices, where the indices are specified relative to the current maximum vertex position (-1 references the last vertex defined). 

--

## Face Format

- This makes it easy to describe the points in a face, then the face, without the need to store a large list of points and their indexes. In this way, "v" commands and "f" commands can be interspersed.

```
v -0.500000 0.000000 0.400000
v -0.500000 0.000000 -0.800000
v -0.500000 1.000000 -0.800000
v -0.500000 1.000000 0.400000
f -4 -3 -2 -1

```

---

# Other formats

- whilst obj is a serialization (file) format it demonstrates principles used internally in DCC tools and renderers
- Having an understanding of the basics help to learn new formats
- Usually I try to generate a simple triangle then extrapolate from there
- The following examples will demonstrate this and we will also look at other formats (for example in renderman)

--

## [```MfnMesh```](https://help.autodesk.com/view/MAYAUL/2017/ENU/?guid=__py_ref_class_open_maya_1_1_m_fn_mesh_html)

```python
import maya.cmds as cmds
import maya.api.OpenMaya as OpenMaya

numVertices=3
numFaces=1

outputMesh = OpenMaya.MObject()
points = OpenMaya.MFloatPointArray()
faceConnects = OpenMaya.MIntArray()
faceCounts = OpenMaya.MIntArray()

p = OpenMaya.MFloatPoint(-1.0,0.0,-1.0)
points.append(p)
p = OpenMaya.MFloatPoint(0.0,0.0,1.0)
points.append(p)
p = OpenMaya.MFloatPoint(1.0,0.0,-1.0)
points.append(p)
faceConnects.append(0)
faceConnects.append(1)
faceConnects.append(2)
faceCounts.append(3)

meshFN = OpenMaya.MFnMesh()

meshFN.create(points,faceCounts,faceConnects)
nodeName = meshFN.name()
print(nodeName)
cmds.sets(nodeName, add='initialShadingGroup')  
cmds.select(nodeName)  
meshFN.updateSurface()
```

--

## MfnMesh

- As is typical with most mesh formats we have lists
  - in this case we have face counts and face connects
- This allows the mesh to have multiple faces of different sizes (Tri, Quad, Polygon)
- Each of these lists index from 0

---

## [Houdini Simple Poly](https://www.sidefx.com/docs/houdini/hom/hou/Face.html#addVertex)

```
node = hou.pwd()
geo = node.geometry()

# Add code to modify contents of geo.
# Use drop down menu to select examples.
node = hou.pwd()
geo = node.geometry()
poly = geo.createPolygon()

p=[(-1,0,-1),(0,0,1),(1,0,-1)]

points=geo.createPoints(p)
for p in points :
    poly.addVertex(p)

```

---

## References and Links

- [Mark Elendt CPP Con talk on Houdini](https://www.youtube.com/watch?v=2YXwg0n9e7E&t=4s&ab_channel=CppCon)

- [Houdini You're Learning it wrong Matt Estela](https://www.youtube.com/watch?v=KONIvmOELu8&ab_channel=Houdini)

- [Points and Verts and Prims](https://www.tokeru.com/cgwiki/index.php?title=Points_and_Verts_and_Prims)