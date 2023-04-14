## Let's talk about Data
### serialization,formats and schema's

Jon Macey

jmacey@bournemouth.ac.uk

---

## Introduction

- Formatted data is the core to most animation pipelines
- There are many formats we can use to store data
  - in this lecture we will look at some of the more common ones
- But first we need to look at the wider picture

--

## What comes first Saving or Loading?

- Typically we design data formats around a specification
  - In animation tools we are saving structured data (Vertex?)
- In programs we are saving state 
  - however sometimes we save both program state and structured data (Maya scenes, hip files etc.)
- What to do is dependent upon context

--

## Serialization (CompSci)

- is the process of translating a data structure or object state into a format that can be stored
  - typically this means files but could be for transmission (network)
- deserialization is the loading of this data back into the object or structures
- Usually we need to add extra information about the saved data as the receiving object need to know about amount.

--

## Serialization 

- some languages have this built in (not C / C++)
- in most cases we can use a library or 3rd party format.
- C++ 
  - [Boost.Serialization](https://www.boost.org/doc/libs/1_81_0/libs/serialization/doc/index.html) [ProtoBuf](https://protobuf.dev/)
- Python [```import pickle```](https://docs.python.org/3/library/pickle.html) 
- most people now use [json](https://www.json.org/json-en.html) as the core format with some [yaml](https://yaml.org/) or [toml](https://toml.io/en/).

--

## Serialization

- Most formats will have a library use them!
  - for example [rapidxml](https://rapidxml.sourceforge.net/) and [rapidjson](https://rapidjson.org/) are part of NGL
- Most DCC tools will ship with C++ and python libraries that allow us to read and write the file formats
- 3rd party library support for others ([FBX](https://www.autodesk.com/products/fbx/overview),[Collada](https://www.khronos.org/collada/),[Alembic](https://www.alembic.io/),[USD](https://www.openusd.org/release/index.html))

--

## Renderers

- As seen with Renderman rib most renderers have file / scene formats too
- These are generally much simpler than DCC formats
- We will most likely not look too much at these but the principles are similar to other DCC tools so easy to pickup.

---

## Program Serialization 

- There are many ways to save and load program state and data
- We can use 3rd party libraries or use our own formats
  - either way is acceptable and usually depends upon context
- The following examples do simple object serialization 

--

## [Boost.Serialization](https://www.boost.org/doc/libs/1_81_0/libs/serialization/doc/index.html)

- A reversible deconstruction of an arbitrary set of C++ data structures to a sequence of bytes. 
- In Boost.Serialization they use the term "archive" to refer to a specific rendering of this stream of bytes. 
- By overloading a template Archive class we can write and read our data.

--

## C++ example 

- A simple Sphere class with x,y,z parameters a std::string for a name and a double as radius.

```c++
// When the class Archive corresponds to an output archive, the
// & operator is defined similar to <<.  Likewise, when the class Archive
// is a type of input archive the & operator is defined similar to >>.
template<class Archive>
/// @brief the serialize method using boost::serialize
/// @param the archive to output to

void serialize(Archive & _ar, const unsigned int)
{
    _ar & m_name;
    _ar & m_x;
    _ar & m_y;
    _ar & m_z;
    _ar & m_radius;
}
```

--

# [main.cpp](https://github.com/NCCA/PipelineAndTD/blob/main/DataLecture/BoostSerialization/src/main.cpp)

```c++
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Sphere.h"

int main()
{
  std::cout<<"creating object\n";
  Sphere s1("Sphere1 test 1 2",0.0f,2.4f,0.4f,2.3l);
  std::cout<<s1<<"\n\n";
  std::ofstream ofs("Sphere.txt");
  // save data to archive
  {
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << s1;
    // archive and stream closed when destructors are called
  }
  Sphere s2;
  std::cout<<"created Empty object \n";
  std::cout<<s2<<"\n\n";
  {
    // create and open an archive for input
    std::ifstream ifs("Sphere.txt");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> s2;
    // archive and stream closed when destructors are called
  }
  std::cout<<s2<<"\n\n";
  return EXIT_SUCCESS;
}


```


--

## Python [pickle](https://docs.python.org/3/library/pickle.html)

- The pickle module can be used to serialize python objects
- a byte stream can be used to re-create the original object hierarchy by unpickling the stream
- the pickle module creates an instance of the original object first and then populates the instance with the correct data. 


--

## pickle types

- pickle can serialize the following types
  - None, true, and false
  - Numeric types 
  - Normal and Unicode strings
  - Tuples, lists, sets, and dictionaries containing only picklable objects
  - Functions defined at the top level of a module
  - Built-in functions defined at the top level of a module
  - Classes that are defined at the top level of a module

--

## example [Sphere.py]()

```python
#!/usr/bin/env python
import pickle

class Sphere :
    def __init__(self,name : str, x : float, y : float, z : float , radius : float ) -> None :
        self.name=name
        self.x=x
        self.y=y
        self.z=z
        self.radius=radius
    def __str__(self) -> str:
        return f"{self.name=} {self.x=} {self.y=} {self.z=} {self.radius=}"

if __name__ =="__main__" :
    s=Sphere("test",2.0,0.0,1.0,2.3)

    with open("sphere","wb") as file :
        pickle.dump(s,file)

    with open("sphere","rb") as file :
        n=pickle.load(file)
        print(n)
```

---

## [QSettings](https://doc.qt.io/qt-6/qsettings.html)

- The QSettings class provides persistent platform-independent application settings.
- Users normally expect an application to remember its settings (window sizes and positions, options, etc.) across sessions. 
- Different OS's use different systems
  - Windows the system registry
  - MacOS and iOS property lists files
  - Unix INI files
- QSettings abstracts these to a single class

--

## [QSettings](https://doc.qt.io/qt-6/qsettings.html)

- Based on QVariant, allowing you to save most value-based types, such as QString, QRect, and QImage
- When creating a QSettings object, you must pass the name of your company or organization as well as the name of your application (standard with most apps now)

```c++
QSettings settings("NCCA", "ClutterBase");
```

- This can also be done using the core application module as well

```c++
QCoreApplication::setOrganizationName("NCCA");
QCoreApplication::setOrganizationDomain("ncca.bournemouth.ac.uk");
QCoreApplication::setApplicationName("ClutterBase");
QSettings settings;
```

--

## [Settings.py](https://github.com/NCCA/PipelineAndTD/blob/main/DataLecture/QSettings/Settings.py)

```python
#!/usr/bin/env python
try:  #  support either PyQt5 or 6
    from PyQt5 import uic
    from PyQt5.QtCore import *
    from PyQt5.QtGui import QCloseEvent
    from PyQt5.QtWidgets import QApplication, QMainWindow

    PyQtVersion = 5
except ImportError:
    print("trying Qt6")
    from PyQt6 import uic
    from PyQt6.QtCore import *
    from PyQt6.QtGui import QCloseEvent
    from PyQt6.QtWidgets import QApplication, QMainWindow
    PyQtVersion = 6

import sys


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.settings = QSettings("NCCA", "NCCA_Settings_Demo")
        self.load_settings()

    def load_settings(self) :
        self.resize(self.settings.value("size", QSize(100, 100)))

    def save_settings(self)   :
        self.settings.setValue("size", self.size())  

    def closeEvent(self, event: QCloseEvent) -> None:
        self.save_settings()


if __name__ == "__main__":
    app = QApplication([])
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())

```

--

## QSettings

- it is possible to group settings and save many types
- this can get quite large so we can split this into many sections / functions
- I have a slightly more complex example of using this in my [MayaEditor](https://github.com/NCCA/MayaEditor/blob/main/plug-ins/MayaEditorCore/EditorDialog.py) code.
- The C++ approach is similar to the python one

---

## [Protocol Buffers](https://protobuf.dev/)

- Protocol Buffers are a language-neutral, platform-neutral extensible mechanism for serializing structured data.
- It works by defining a "Message" structure to be serialized.  

```
message Person {
  optional string name = 1;
  optional int32 id = 2;
  optional string email = 3;
}
```

--

## Compiler

- The ```protoc``` compiler takes an input file describing the data and then generates code for reading and writing this data in a formatted way.
- We can use this directly in [CMake](https://cmake.org/cmake/help/latest/module/FindProtobuf.html) when using C++ or generate python code to read and write our data.
- For C++, the compiler generates a .h and .cc file from each .proto, with a class for each message type described in your file.

--

## Proto file format

- Proto1 is deprecated.
- Proto3 is a simplification of Proto2. 
- Both Proto2 and Proto3 are active
- Will use Proto2 as more complex an needs more explanation.

--

## [scene.proto](https://github.com/NCCA/PipelineAndTD/blob/main/DataLecture/Protobuf/scene.proto)

```
syntax = "proto2";
package NCCA;

message Asset {
  required string name = 1;
  required int32 id = 2;
  optional string description = 3;

  enum AssetType {
    FBX = 0;
    USD = 1;
    COLLADA = 2;
  }

  message MeshType {
    required string location = 1;
    optional AssetType type = 2 [default = USD];
  }

  repeated MeshType meshes = 4;
}

message Scene {
  repeated Asset assets = 1;
}

```

--

## C++ Demos

- there are two demos 
- [write.cpp](https://github.com/NCCA/PipelineAndTD/blob/main/DataLecture/Protobuf/write.cpp) to generate or append to a file
- [read.cpp](https://github.com/NCCA/PipelineAndTD/blob/main/DataLecture/Protobuf/read.cpp) to read in the existing scene file.

--

## Python

- need to ```pip install protobuf``` first so we have the python module

- Next we need to run the protoc tool on the .proto file for a schema, this is located here

```
/public/devel/2022/vcpkg/installed/x64-linux/tools/protobuf/protoc
``` 

- we need to add flags for python as follows   

```
-I. --python_out=. scene.proto
```

- this will generate the file scene_pb2.py which is included in the demo

--

## [read.py](https://github.com/NCCA/PipelineAndTD/blob/main/DataLecture/Protobuf/read.py)

- the data is loaded into a python dictionary so is easy to process 

```python
#!/usr/bin/env python

import pprint
import sys

import scene_pb2

if __name__ == "__main__" :

    # Main procedure:  Reads the entire address book from a file and prints all
    #   the information inside.
    if len(sys.argv) != 2:
        print ("Usage: {sys.argv[0]} scene file")
        sys.exit(-1)

    scene = scene_pb2.Scene()

    # Read the existing address book.
    f = open(sys.argv[1], "rb")
    scene.ParseFromString(f.read())
    f.close()
    pprint.pprint(scene)
```

---

## Schemas

- "a representation of a plan or theory in the form of an outline or model". "a schema of scientific reasoning"
- To us a way of representing data typically in a database but also for structured file data.
- Most file format specifications have a schema too
  - [xml](https://www.w3.org/standards/xml/schema)
  - [json](https://json-schema.org/)
  - [USD](https://openusd.org/release/tut_generating_new_schema.html)

--

## Some terms

- [DOM](https://en.wikipedia.org/wiki/Document_Object_Model) document object model 
  - "is a cross-platform and language-independent interface that treats an HTML or XML document as a tree structure wherein each node is an object representing a part of the document"
- [SAX](https://en.wikipedia.org/wiki/Simple_API_for_XML) Simple API for XML A programming interface (API) for accessing the contents of an XML
- [expat](https://libexpat.github.io/) Expat, a stream-oriented XML parser library written in C great for large files


---

## XML eXtensible Markup Language

- Doesn't really do anything just contains data, we use <tags> </tags> like html but define our own
- Uses much more space as needs open and close tags 
- XML forms a tree structure using <> tags to enclose the different elements

 ```
<?xml version="1.0" encoding="UTF-8"?>
<NCCAModelViewer>
  <keyLight>
    <position>-2 1 1 </position>
    <active>1</active>
    <colourSlider>153</colourSlider>
    <colour>153 153 153</colour>
    <specSlider>153</specSlider>
    <specColour>76 76 76</specColour>
  </keyLight>
</NCCAModelViewer>
```

--

## Escaping
- XML provides escape facilities for including characters which are problematic to include directly.
```
&lt; represents <
&gt; represents >
&amp; represents &
&apos; represents '
&quot; represents "
```

--

## XML Usage 

- Most DCC tools use XML for setup and parameters
  - Maya uses it for the render node descriptions in hypershade
  - The render description files for the renderers
  - Houdini Menus and tabs are xml files
  - Houdini shelves are xml (but with a .shelf extension)
- There are many more cases, this is a legacy and is gradually changing to json.

--

## XML libraries

- There are many xml libraries we can use
  - C++ I suggest [RapidXML](https://github.com/Fe-Bell/RapidXML)
  - if using Qt they have their own [QtXml](https://doc.qt.io/qt-5/qtxml-index.html)
- The python standard library has an [xml](https://docs.python.org/3/library/xml.html) module
  - there are many more 3rd party ones to choose as well

--

## Designing data formats
- Writing XML files is largely up to the developer 
- We specify the format we need and which data tags are required
- These can then be written to the file using normal file writing processes

--

## Point Bake Format

```
<?xml version="1.0" encoding="UTF-8" ?>
<NCCAPointBake>
  <MeshName> polySurface1 </MeshName>
  <NumVerts> 912 </NumVerts>
  <StartFrame> 0 </StartFrame>
  <EndFrame> 151 </EndFrame>
  <NumFrames> 151 </NumFrames>
  <TranslateMode> absolute </TranslateMode>
  <Frame number="0">
  </Frame>
</NCCAPointBake>
```

--

## Per Vertex Data

```
<Vertex number="0" attrib="translate"> -0.103412 15.294069 3.914999 </Vertex>
<Vertex number="1" attrib="translate"> -0.114753 15.167216 3.920175 </Vertex>
<Vertex number="2" attrib="translate"> -0.073407 15.167994 3.865294 </Vertex>
<Vertex number="3" attrib="translate"> -0.075351 15.262026 3.872085 </Vertex>
```
- The per vertex values are written out as shown above
- The attribute is used to indicate what the data is
- Then the actual point data is written

--


## Demos

- There are a series of demos for thing in the following repo https://github.com/NCCA/PointBake 
- Simple scripts to export and load from maya and C++ code for NGL
- There is also another example to import into Houdini


---

##



