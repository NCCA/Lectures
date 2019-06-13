# Maya API :- Computation, Iterators and Exporters

Jon Macey

---

## MComputation
- MComputation allows long computations / processes to check for user interrupts (usually the esc key)
- The process is simple, before any computation we create an instance of the MComputation class
  - call the beginComputation() method
  - check for interrupts using isInterruptRequested()
- this is shown in the following example

--

## MComputation

```
#include <maya/MSimple.h>
#include <maya/MIOStream.h>
#include <maya/MGlobal.h>
#include <maya/MComputation.h>
// This is a macro to create a simple command
// the compiler expands it to a bunch of code

DeclareSimpleCommand( MComputationTest , "NCCA", "Any");

MStatus MComputationTest::doIt( const MArgList& )
{

  // create an MComputation class for heavy calculation type things
  MComputation Interupter;

  // set the start of the heavy computation
  Interupter.beginComputation();

  while(1)
  {
    MGlobal::displayInfo("doing a computation press ESC to stop");
    // just a little sleep loop so we don't thrash things too much
    for(int i=0; i<99999999; ++i){;}
    if( Interupter.isInterruptRequested() )
    {
      Interupter.endComputation();
      MGlobal::displayInfo("intrupted by escape");
      return MS::kFailure;
    }
  }
}
```

--

## Python Version
- you can also use MComputation in python as well

```
import maya.OpenMaya as OM

# as these can take time to process we have an interupter to allow for the process to be
# stopped
interupter=OM.MComputation()
# set the start of the heavy computation
interupter.beginComputation()

while  True :
  if interupter.isInterruptRequested()  :
    print "intrupted by escape"
    interupter.endComputation();
    quit=True
    break
  for i in range(0,999):
    print '.',

```

---

## selection and iteration
- One of the easiest ways for a command to access element from maya is via the use of selection lists
- The MGlobal class has a number of methods which will return selection lists depending upon different criteria
- It will fill an MSelectionList object with the currently selected MObjects
- This can then be used to manipulate the list such as add/remove values

--

## MFnDagNode
- The DAG is a graph that describes the hierarchy of the objects in the model. 
- At each level of the hierarchy there is a four by four transformation matrix that affects all of the objects beneath it in the DAG.
- MFnDagNode = DAG Node Function Set.
- Provides methods for attaching Function Sets to, querying, and adding children to DAG Nodes. 

--

## [example](https://github.com/NCCA/MayaAPICode/tree/master/Lecture3/GetSelection)

```
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MDagPath.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MIOStream.h>

// This is a macro to create a simple command
// the compiler expands it to a bunch of code

DeclareSimpleCommand( GetSelection , "NCCA", "Any");

MStatus GetSelection::doIt( const MArgList& )
{

  MDagPath node;
  MObject component;
  MSelectionList list;
  MFnDagNode nodeFn;
  // get the currently selected objects
  MGlobal::getActiveSelectionList( list );
  // get the size of the list
  uint size=list.length();
  for (uint  i=0; i< size; ++i )
  {
    // get the DAG path for this object and place the node and component values
    list.getDagPath( i, node, component );
    // attach the found node to the DagNode function set
    nodeFn.setObject( node );
    // now use this to get the object name and display
    MGlobal::displayInfo("Object "+nodeFn.name()+ " is selected");
  }
  return MS::kSuccess;
}
```

--

## [example](https://github.com/NCCA/MayaAPICode/tree/master/Lecture3/GetSelection)

- Once the list has been selected we use the getDagPath method to return the object as a MDagPath
- The setObject method of the MFnDagNode is then used to attach a function set to the DagNodes
- Finally we use this to access the actual attribute data of the node

---

## [MItDag](https://github.com/NCCA/MayaAPICode/tree/master/Lecture3/DAGIt)
- The following example shows how to iterate the whole of the DAG
- This will be used to grab each object in turn and print out information about it 

```
// Object pPrism1 type transform // 
// fullPathName |pPrism1 // 
// partialPathName pPrism1 // 
// Parent path pPrism1 // 
// Parent namespace  // 
// number of children= 1 number of parents= 1  // 
// attribute count = 207  // 
// Transformation Matrix // 
// [2.9886,0.0000,-0.2615,0.0000] // 
// [1.9924,1.0000,-0.1743,0.0000] // 
// [0.0872,0.0000,0.9962,0.0000] // 
// [-5.6357,5.7134,-8.0560,1.0000] // 
```

--

## [MItDag](https://github.com/NCCA/MayaAPICode/tree/master/Lecture3/DAGIt)

```
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MDagPath.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MIOStream.h>
#include <maya/MItDag.h>
#include <maya/MMatrix.h>

// This is a macro to create a simple command
// the compiler expands it to a bunch of code

DeclareSimpleCommand( DAGit , "NCCA", "Any");

MStatus DAGit::doIt( const MArgList& )
{

  MItDag dagIt (MItDag::kBreadthFirst);
  MFnDagNode nodeFn;
  MObject node;
  uint count=0;
  char msg[50];

  MGlobal::displayInfo("traversing DAG");
  for (dagIt.next(); !dagIt.isDone(); dagIt.next())
  {
    node = dagIt.item();
    nodeFn.setObject( node );
    if( node.hasFn(MFn::kNamedObject))
    {
      MGlobal::displayInfo("Object "+nodeFn.name()+ " type " + nodeFn.typeName());
      MGlobal::displayInfo("fullPathName "+nodeFn.fullPathName());
      MGlobal::displayInfo("partialPathName "+nodeFn.partialPathName());
      MGlobal::displayInfo("Parent path "+nodeFn.partialPathName());
      MGlobal::displayInfo("Parent namespace "+nodeFn.parentNamespace());
      sprintf(msg,"number of children= %d number of parents= %d ",nodeFn.childCount(),nodeFn.parentCount());
      MGlobal::displayInfo(msg);
      sprintf(msg,"attribute count = %d ",nodeFn.attributeCount());
      MGlobal::displayInfo(msg);
      MGlobal::displayInfo("Transformation Matrix");
      MMatrix m=nodeFn.transformationMatrix();
      sprintf(msg,"[%02.4lf,%02.4lf,%02.4lf,%02.4lf]",m(0,0),m(0,1),m(0,2),m(0,3));
      MGlobal::displayInfo( msg);
      sprintf(msg,"[%02.4lf,%02.4lf,%02.4lf,%02.4lf]",m(1,0),m(1,1),m(1,2),m(1,3));
      MGlobal::displayInfo( msg);
      sprintf(msg,"[%02.4lf,%02.4lf,%02.4lf,%02.4lf]",m(2,0),m(2,1),m(2,2),m(2,3));
      MGlobal::displayInfo( msg);
      sprintf(msg,"[%02.4lf,%02.4lf,%02.4lf,%02.4lf]",m(3,0),m(3,1),m(3,2),m(3,3));
      MGlobal::displayInfo( msg);

      MGlobal::displayInfo("*********************************************************************");
      ++count;
    }

  }
  sprintf(msg,"found %d objects",count);
  MGlobal::displayInfo(msg);

  return MS::kSuccess;
}
```

---

## MAnimControl
- Control over animation playback and values.
- This class provide access to the values that control how an animation is played. 
- This includes the minimum and maximum frames included in the playback, whether the playback loops, and whether the animation runs in all views, or only the active view.
- Methods also exist that mirror the functionality of the controls found on the time slider in the UI to start and stop the playback.

--

## MAnimControl
- To use this functionality we need to link with the library OpenMayaAnim
- Most of the control parameters need to be set using an MTime object and these will set / get float values
- This is shown in the following example

--

## [example](https://github.com/NCCA/MayaAPICode/tree/master/Lecture3/Frames)

```
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MIOStream.h>
#include <maya/MAnimControl.h>
#include <maya/MTime.h>
// This is a macro to create a simple command
// the compiler expands it to a bunch of code

DeclareSimpleCommand( TimeLine , "NCCA", "Any");

MStatus TimeLine::doIt( const MArgList& )
{

  MTime currframe;
  MAnimControl anim;
  // lets set the min time
  currframe.setValue(0);
  anim.setMinTime(currframe);
  // lets set the max time
  currframe.setValue(10000);
  anim.setMaxTime(currframe);

  // now lets accesss this info
  char msg[100];
  sprintf(msg,"start frame =%f",anim.animationStartTime().value() );
  MGlobal::displayInfo(msg);
  sprintf(msg,"end frame =%f",anim.animationEndTime().value() );
  MGlobal::displayInfo(msg);
  int end=anim.animationEndTime().value();
  for(int i=0; i<end; ++i)
  {
    currframe.setValue(i);
    anim.setCurrentTime(currframe);
    sprintf(msg,"frame =%f",anim.currentTime().value() );
    MGlobal::displayInfo(msg);
  }

  return MS::kSuccess;
}
```

---

## MPxFileTranslator
- This class provides a base class from which one derives in order to implement Maya "File Translator Plug-Ins." 
- A file translator plug-in allows Maya to read or write 3rd party file formats.
- These will appear in the list for the export / export selection
- The user must implement a reader and or writer function to do the translation

--

## MPxFileTranslator
- The reader / writer methods will be passed the full path of the file selected from the file dialog
- A string containing the options passed to the file command
- A flag to indicate how this was invoked (for example export vs export selection)

--

## example [Rib Exporter](https://github.com/NCCA/MayaAPICode/tree/master/Lecture3/RibExporter)
- The following example will export the current scene to a renderman rib file
- It gathers scene information from the render globals 
  - output filename
  - image size
  - frames to render (start/end step padding)
- The user can also indicate if UV’s Normals Geo and Lights should be exported

--

## output

```
# rib export Maya Script
Display "TestScene.001.exr" "file" "rgba"
Format 1280 720 0.999563
Projection "perspective" "uniform float fov" [39.8873]
Identity
# camera tx
Scale 1 1 -1
ConcatTransform [  0.557514  -0  -0.830167  -0  -0  1  -0  0  0.830167  -0
     0.557514  -0  -0.0103964  -0.889608  -8.88744  1  ]
WorldBegin
TransformBegin
Identity
# exporting maya mesh pPlaneShape1
ConcatTransform [  1  0  0  0  0  1  0  0  0  0  1  0  0  0  0  1  ]
Polygon "vertex point P" [-6 -1.33227e-15 6 -5.7 -1.33227e-15 6 -5.7 -1.265
    65e-15 5.7 -6 -1.26565e-15 5.7 ] "varying normal N" [0 1 2.22045e-16 0
    1 2.22045e-16 0 1 2.22045e-16 0 1 2.22045e-16 ] "varying float[2] st" [
    0 0 0.025 0 0.025 0.025 0 0.025 ]
TransformEnd
WorldEnd
```

--

## exporter outline
1. read options and setup environment
2. grab render globals
3. create interputer
  - Loop for each frame
  - export Display / Format
  - export Camera
  - export Lights (not implemented)
  - export geometry

--

## command options
- The writer function is passed a string with the options passed
- In this example the following options are used
  - -normals
  - -uvs
  - -geo
  - -lights
- They are passed in a ; separated string like this   

```
"-normals=1;-uvs=1;-geo=1;-lights=1";
```

--

## command line parsing

```
void RibExport::parseCommandOptions(const MString& _optionsString)
{

  //	process the option string passed in from the option script
  //
  if (_optionsString.length() > 0)
  {

    int i, length;
    // Start parsing.
    MStringArray optionList;
    MStringArray theOption;

    //	each option is in the form -
    //	[Option] = [Value];
    //
    //	the options are therefore split by the semi-colons
    //
    _optionsString.split(';', optionList);

    //	process each option in the string
    //
    length = optionList.length();
    for( i = 0; i < length; ++i )
    {
      theOption.clear();

      //	split the option using the '=' character. This should make
      //	theOption[0] hold the option name, and theOption[1] hold the
      //	value of the current option
      //
      optionList[i].split( '=', theOption );
      MGlobal::displayInfo(theOption[0]);
      if( theOption[0] == "-normals" && theOption.length() > 1 )
      {
        if(theOption[1].asInt()>0)
          m_exportNormals = true;
        else
          m_exportNormals = false;
      }

      else if( theOption[0] == "-uvs" && theOption.length() > 1 )
      {
        if(theOption[1].asInt()>0)
          m_exportUV = true;
        else
          m_exportUV = false;
      }
      else if( theOption[0] == "-geo" && theOption.length() > 1 )
      {
        if(theOption[1].asInt()>0)
          m_exportMesh= true;
        else
          m_exportMesh = false;
      }

      else if( theOption[0] == "-lights" && theOption.length() > 1 )
      {
        if(theOption[1].asInt()>0)
          m_exportLights= true;
        else
          m_exportLights = false;
      }

     }
  }
}
```

--

## render globals
- The MCommonRenderSettingsData class allows access to the render globals dialog (specifically the common settings)
- This doesn’t include the current selected camera but most other things are here
- The following code grabs them and sets the class attributes. 

--

## render globals

```
void RibExport::getRenderGlobals()
{
  MCommonRenderSettingsData data;
  MRenderUtil::getCommonRenderSettings(data);
  m_startFrame=int(data.frameStart.value());
  m_endFrame=int(data.frameEnd.value());
  m_frameStep=int(data.frameBy);
  m_imageName=data.name;

  if (m_imageName.length() ==0)
  {
    MGlobal::displayWarning("No filename set in render globals, using default");
    m_imageName="noNameSet";
  }
  m_pixelAspectRatio=data.pixelAspectRatio;
  m_imageWidth=data.width;
  m_imageHeight=data.height;
  m_framePad=data.framePadding;

}
```

--

## camera export
- To export the camera we create a DG iterator for just cameras
- A plug is then created for the “renderable” attribute which is check to see if the camera is the currently selected one in the render settings
- The camera is then queries to get the data for renderman by getting the “inclusiveMatrixInverse”
- This is shown in the following code

--

## camera export

```
MStatus RibExport::exportCamera()
{

  MItDependencyNodes it(MFn::kCamera);
  MFnDagNode nodeFn;
  MStatus status;
  // keep looping until done
  while(!it.isDone())
  {

  // get a handle to this node
  MFnCamera cam ( it.item());
  // the active renderable camera is not stored in the render globals but in the
  // camera itself so we get the value here and output if set
  bool renderable;
  cam.findPlug( "renderable" ).getValue( renderable );

  if(renderable)
  {

    m_stream<<"Projection \"perspective\" \"uniform float fov\" [";
    // using the following calculation
    // http://drakeguan.org/node/393
    // FOV = rad_to_deg(2*atan((xres/yres)*12.7/cam.focalLength))
    double fl=cam.focalLength();
    double fov= 2*atan((m_imageWidth/m_imageHeight)*12.7/fl);
    m_stream<<(fov/ M_PI) * 180.0f;
    m_stream<<"]\n";

    MDagPath path;

    // getAllPaths() would be better here (to support instancing).
    // IIRC, cameras get very screwy when instanced, so don't worry too much
    status = cam.getPath(path);
    CHECK_STATUS_AND_RETURN_IF_FAIL(status," error getting path ");

    // if you want the world space (or inverse) matrices it's always better to grab those from the
    // dag path directly. (It avoids the annoyance of having to use the MFnMatrixData class).
    // inclusiveMatrix() is the same as the world matrix.....  If you have the path, everything preceding
    // this bit can be ignored ;)
    MMatrix tx = path.inclusiveMatrixInverse(&status);
    CHECK_STATUS_AND_RETURN_IF_FAIL(status," error getting inverse matrix ");

    // now export first set the identity matrix
    m_stream<<"Identity \n";
    // flip the z for the camera
    m_stream<<"# camera tx \n";
    // now flip the Z for prman (could do this in the transform but this is easier!)
    m_stream<<"Scale 1 1 -1 \n";

    // now the tx matrix
    m_stream<<"ConcatTransform [ ";
    for(int y=0; y<4; ++y)
      for(int x=0; x<4; ++x)
        m_stream<<" "<<tx(y,x)<<" ";
    m_stream<<" ]\n";
    // as we only want one camera we can return from this function now
    return MS::kSuccess;
  }
  // move on to next node
  it.next();

  }
  return MS::kSuccess;
}
```

--

## iterating lights

```
if(m_exportLights)
    {
      MItDependencyNodes lightIt(MFn::kLight);
      // keep looping until done
      while(!lightIt.isDone())
      {
      // get a handle to this node
      MObject obj( lightIt.item());
      exportLight(obj);
      // move on to next node
      lightIt.next();
      }
    }

```

--

## iterating meshes

```
if(m_exportMesh)
    {
      MItDependencyNodes meshIt(MFn::kMesh);
      // keep looping until done
      while(!meshIt.isDone())
      {

      // get a handle to this node
      MObject obj = meshIt.item();

        exportMesh(obj);
      // move on to next node
      meshIt.next();

      }
    }
```

--

## MDagPath
- Use this DAG Path Class to obtain and query Paths to DAG Nodes. 
- A DAG path is a path from the world node to a particular object in the DAG.
- Use this class in conjunction with the DAG Iterator (MItDag), DAG Node Function Set (MFnDagNode) and DAG Path Array class (MDagPathArray) to query and edit the DAG.

--

## inclusiveMatrix
- The matrix for all Transforms in the Path including the the end Node in the Path if it is a Transform
- The following code gets the total transform for the mesh

```
  MDagPath path;

  status = mesh.getPath(path);
  CHECK_STATUS_AND_RETURN_IF_FAIL(status," error getting path ");

  // if you want the world space (or inverse) matrices it's always better to grab those from the
  // dag path directly. (It avoids the annoyance of having to use the MmeshMatrixData class).
  // inclusiveMatrix() is the same as the world matrix.....  If you have the path, everything preceding
  // this bit can be ignored ;)
  MMatrix tx = path.inclusiveMatrix(&status);
  CHECK_STATUS_AND_RETURN_IF_FAIL(status," error getting inverse matrix ");

  m_stream<<"# exporting maya mesh "<<mesh.name()<<"\n";
  // now the tx matrix
  m_stream<<"ConcatTransform [ ";
  for(int y=0; y<4; ++y)
    for(int x=0; x<4; ++x)
      m_stream<<" "<<tx(y,x)<<" ";
  m_stream<<" ]\n";

```

--

## accessing vertex data
- The vertex and normal data is easy to access, using the methods shown below. 
- This will return an array of the unique data which the mesh faces index into

```
// this will hold the returned vertex positions
MPointArray vts;
// use the function set to get the points
mesh.getPoints(vts);
// now the normals
MFloatVectorArray nmls;
// use the function set to get the points
mesh.getNormals(nmls);
```

--

## Texture co-ordinates
- A mesh may hold a varying number of uv sets.
- This means that you will have to deal with the possibility of no texture co-ordinates on a mesh, or optionally, more than one set.
- If no uv’s exist the MayaAPI will still return one to you. 
- To get around this problem, it is worth querying the length of the first uv set to see if it actually contains any data before writing out that UV Set.

--

```
MStringArray uvsets;
// get the names of the uv sets on the mesh
mesh.getUVSetNames(uvsets);
MStringArray sets;
// get the names of the uv sets on the mesh
mesh.getUVSetNames(sets);

// set a usage flag for texture coords
bool bUvs = ((sets.length()!=0) && (mesh.numUVs()>0));
MFloatArray uArray;
MFloatArray vArray;
mesh.getUVs(uArray,vArray);
```

--

## MItMeshPolygon
- This class is the iterator for polygonal surfaces (meshes).
- The iterator functions in two modes depending on whether a component is specified. 
- When a component is not given or is NULL the iteration will be over all polygons for the surface. 
- When a component is given this iterator will iterate over the polygons (faces) specified in the component. 

--

## MItMeshPolygon
- We then use the methods to access the index into the data we have gathered from the meshes. 
- In this case we get the vertex count using the polygonVertexCount() method
- Then vertexIndex() normalIndex() getUVIndex() to get the data.
- This is shown in the next slide

--

```
  // attach an iterator to the mesh
  MItMeshPolygon itPoly(_node);

  // now loop through the mesh and export
  while(!itPoly.isDone())
  {
// Polygon "varying float[2] st" [] "vertex point P" [] "varying normal N" []
    auto vc = itPoly.polygonVertexCount();
    // in this case we are going to do normal prman polygons and have options to export uv / normals
    m_stream<<"Polygon ";

    m_stream<<"\"vertex point P\" [";
    for(auto i=0; i<vc; ++i)
    {
      uint index=itPoly.vertexIndex(i);
      m_stream<<vts[index][0]<<" "<<vts[index][1]<<" "<<vts[index][2]<<" ";
    }
    m_stream<<"] ";
    if(m_exportNormals)
    {
      m_stream<<  "\"varying normal N\" [";
      for(auto i=0; i<vc; ++i)
      {
        uint index=itPoly.normalIndex(i);
        m_stream<<nmls[index][0]<<" "<<nmls[index][1]<<" "<<nmls[index][2]<<" ";
      }
      m_stream<<"] ";
    }
    if(bUvs && m_exportUV)
    {
      m_stream<<"\"varying float[2] st\" [";
    // have to get the uv index seperately
      for(auto i=0; i<vc; ++i)
      {
        int index;
        itPoly.getUVIndex(i,index);
        m_stream<<uArray[index]<<" "<<vArray[index]<<" ";
      }
      m_stream<<"] ";

    }

    m_stream<<"\n";
    itPoly.next();
  }
```

---

## references

- [The maya exporter factfile Rob the Bloke](http://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/research/index.htm)
- The Maya API help pages