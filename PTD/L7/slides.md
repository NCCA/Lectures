# GUI's and HCI
Jon Macey 
jmacey@bournemouth.ac.uk

---

## GUI and HCI

>[User interface design is a subset of a field of study called human-computer interaction (HCI). Human-computer interaction is the study, planning, and design of how people and computers work together so that a person's needs are satisfied in the most effective way.](https://learning.oreilly.com/library/view/the-essential-guide/9780470053423/00_title.html)

--

## HCI

- When designing a GUI we must consider a number of factors
  - What the user wants / expects from the system
  - What physical limitations and abilities people posses  
  - how the users perceptual and information processing systems work
  - what people find enjoyable and attractive to use.

--

## HCI

- This is a huge area of research we will not cover all areas
- The main aim of this introduction is to understand some of the key concepts
- To recognize basic UI requirements (Both TUI and GUI)
- To establish some basic best practice ideas for UI design. 

--

## Interaction Styles

- Command line
- Menu selection
- Form fill-in
- Direct manipulation
- Anthropomorphic

--

## Command Line

- Oldest computer interface 
  - works well in a number of situations (ssh / remote)
  - Powerful but requires knowledge  (no clues)
  - [TUI](https://en.wikipedia.org/wiki/Text-based_user_interface) can help
  - Can chain commands with pipes

--

## Menu Selection

- Selected choices are given to the user
- Can use pointing device or keys
- Uses recognition not recall (see command line)
- Can break complex interactions into smaller steps

--

## Form Fill-in

- Ideal for information collection
  - can validate data as part of process
  - based on a familiar paper based paradigm
- If it is designed well, a form will aid the user in understanding its purpose and allow fast and easy entry of information

--

## Direct Manipulation

- A direct manipulation interface, as found in graphical systems, enables the user to directly interact with elements presented on the screen
- Interaction usually using pointing device
- They navigate the screen and execute commands by using menu bars and pull-down menus.
- For us we also have direct 3D object selection and moving

--

## Anthropomorphic

- An anthropomorphic interface tries to interact with people the same way people interact with each other
- can include :-
  - spoken natural language dialogues
  - hand gestures, facial expressions, and eye movements
- Now also includes VR / AR systems

--

## Web vs GUI

- In recent years there has been a big convergence of web and GUI's
  - Most of the rules are the same however web now needs to be mobile as well as desktop
- Touch devices now very common which add new rules and ideas
- Vast array of web interfaces can be problematic leading to unintuitive processes

---

## Design Principles

- many of the principles used in modern GUI's were developed for the [Xerox Star](https://en.wikipedia.org/wiki/Xerox_Star) system
  - [WYSIWYG](https://en.wikipedia.org/wiki/WYSIWYG)
  - The illusion of manipulable objects
  - Visual order and viewer focus
  - Revealed structure
  - Consistency

--

## General Principles

- [Accessibility](https://www.gov.uk/service-manual/helping-people-to-use-your-service/understanding-wcag)
  - Systems should be designed to be usable, without modification, by as many people as possible.
- Aesthetically Pleasing
  - This is of course subjective
- Availability
  - Make everything available, avoid the use of modes.

--

## General Principles

- Clarity
  - The interface should be visually, conceptually, and linguistically clear
- Compatibility
  - with user, task and product
- Configurability
 - Permit easy personalization, configuration, and reconfiguration of settings 
- Consistency
  - A system should look, act, and operate the same throughout

--

## General Principles

- Control
  - The user must control the interaction.
  Actions should result from explicit user requests.

- Directness
  - Provide direct ways to accomplish tasks.

- Efficiency
  - Minimize eye and hand movements, and other control actions.
  Transitions between various system controls should flow easily and freely.

--

## General Principles

- Familiarity
  - Employ familiar concepts and use a language that is familiar to the user.
- Flexibility
  - be able to work for novice to advanced users
- Forgiveness
  - try to prevent errors but if they do occur allow undo etc.
- Immersion
  - allow immersion with the task at hand

--

## General Principles Obviousness

- A system should be easily learned and understood. A user should know the following:
  - What to look at
  - What it is
  - What to do
  - When to do it
  - Where to do it
  - Why to do it
  - How to do it

--

## General Principles

- Operability
  - Ensure that a system's design can be used by everyone, regardless of physical abilities.
- Perceptibility
  - Assure that a system's design can be perceived, regardless of a person's sensory abilities.
- Positive First Impression
  - especially important for web pages etc.

--

## General Principles

- Predictability
  - Most users are used to certain UI rules and shortcuts
  - ensure these are followed 
- Recovery
  - Undo, but also saving of state between sessions
- Responsiveness
  - should respond to us, and if busy at least let us know

--

## General Principles

- Safety
  - Protect the user from making mistakes
- Simplicity
  - Provide as simple an interface as possible.
- Transparency
  - Permit the user to focus on the task or job, without concern for the mechanics of the interface
- Visibility
  - A system's status and methods of use must be clearly visible.

--

## How many of these rules get broken?

- Our tools are very complex
  - quite a few of these principles are not followed
  - is this bad?
- When creating our own UI's we can try to follow these guidelines
- However we can also add context familiar ones (i.e. translate rotate, scale tools etc)

---

## Practical GUI design

- There are a number of elements that are common in all UI systems
- We will have a look at these and examine the core elements
- We will group them into the most common use cases and names
- In particular we will look at Qt

--

## [UI Design with Qt](https://doc.qt.io/qt-5/qt-gui-concepts.html)

- Qt tries to use the OS native look and feel as much as possible
- This allows consistent app design for the OS from the same source code
- Qt has also added a new scripted UI framework called [QtQuick/QML](https://doc.qt.io/qt-5/qtquick-index.html)

--

## Desktop Qt

- Both PySide / PyQt and C++ use the desktop widgets
  - We can also use QtQuick / QML for desktop apps
  - This can also be extended via [emscripten](https://emscripten.org/docs/compiling/index.html) and [WebAssembly](https://webassembly.org/) to create Web apps

--

## Desktop Qt

- There are a series of standard Dialogs that come with Qt
  - they will try to use the OS versions if present
- These include things such as Files, Fonts, Colour, Messages
- Most will have an Ok and Cancel button but other standard system buttons exist as well

--

## Examples

- The following examples will introduce some of the standard UI elements
- They are written in QtQuick / QML and converted to web using emsripten
- I will also demonstrate the Desktop version using the qml viewer (Qt6 version)

--

## Buttons

- Buttons come in various guises but usually have some form of ```clicked``` event to trigger an action
- It is also possible to have ```pressed``` and ```released``` events 
- Buttons can also be checkable or grouped into what are know as radio buttons
- Typically tool buttons will have icons to give visual clues rather than text.

--

## Buttons

<iframe scrolling="auto" height="400" width="800" src="./Button1/Button1.html" title="Basic Buttons"></iframe>
```
import QtQuick 
import QtQuick.Controls 
import QtQuick.Layouts
Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Button Types")
    GridLayout{
        anchors.fill: parent
        rows:   4
        columns:   3
    Button {
        Layout.row : 0
        Layout.columnSpan : 1
        text: qsTr("Simple Button")
        onPressed : {
            button1action.text = "onPress"
        }

        onReleased: {
            button1action.text = "onReleased"
        }

    }
    Text {
        id : button1action
        Layout.row : 0
        Layout.column : 1
        text : ""
    }
    ButtonGroup {
        id: radioGroup
    }
        RadioButton{
            Layout.row : 1
            Layout.column: 0
            checked: true
            text : qsTr("radio buttons")
              ButtonGroup.group: radioGroup
        }
        RadioButton{
            Layout.row : 1
            Layout.column: 1
            checked: false
            text : qsTr("are")
            ButtonGroup.group: radioGroup
        }
        RadioButton{
            Layout.row : 1
            Layout.column: 2

            checked: false
            text : qsTr("exclusive")
            ButtonGroup.group: radioGroup
        }
        CheckBox{
            Layout.row : 2
            Layout.column : 0
            checked : true
            text : qsTr("check box")
        }
        Text{
            Layout.row : 2
            Layout.column: 1
            text : qsTr("This is a Dialog Button Box")
        }
        DialogButtonBox{
            Layout.row : 2
            Layout.column: 2
            standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

        }

        RoundButton{
            Layout.row : 3
            Layout.column: 0
            text : qsTr("Round Button")
        }
        ToolButton{
            Layout.row : 3
            Layout.column: 1
            icon.name: "edit-cut"
            icon.source: "images/ncca.png"
            icon.width: 200
            icon.height: 100
            text : qsTr("Tool Button")
        }
    }
}
```

--

## Menus

- Menus are used to select actions
  - this can become quite complex (some apps have search options for menus!)
- In recent years menus and toolbars have become more common
- MacOs has different menu systems to other OS as it's always at the top of the screen
- Sub menus and seperators can be used as well as icons / visual clues
- Common operations also have shortcut keys
- Combo Boxes are a type of dialog menu (Enumerated)

--

## Menus

<iframe scrolling="auto" height="300" width="400"  src="./Menu/Menu.html" title="Menus"></iframe>

```
import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Window {
    width: 400
    height: 300
    visible: true
    title: qsTr("Menus")
    ColumnLayout
    {
        spacing: 3
    Button {
        Layout.alignment: Qt.AlignCenter
        id : menubutton
        text : "menu"
        onPressed: {
                contextMenu.popup()
        }

        Action{
            id :  saveAction
            onTriggered : {
            menubutton.text = "Save Pressed"
            }
        }
        Action{
            id :  saveAsAction
            onTriggered : {
            menubutton.text = "Save As Pressed"
            }
        }
        Action{
            id :  newAction
            onTriggered : {
            menubutton.text = "New Pressed"
            }
        }

        Menu {
            id: contextMenu
            MenuItem {
                text: "Save"
                action: saveAction
            }
            MenuItem {
                text: "Save As"
                action: saveAsAction
            }
            MenuItem {
                text: "New"
                action: newAction
            }
            MenuSeparator{}
            MenuItem { text: "Export" }
            MenuItem { text: "Export As" }
            MenuSeparator{}
            Menu{
                id : submenu
                MenuItem{text :"Sub"}
                MenuItem{text :"Menus"}
                MenuItem{text :"Pop Out"}
                MenuItem{text :"But can be difficut"}
                MenuSeparator{}
                Menu {
                    MenuItem{text :"To Navigate"}
                }
            }

        }
    }
    ComboBox {
        Layout.alignment: Qt.AlignCenter
        id: comboBox
        model: ["First", "Second", "Third"]
        onCurrentIndexChanged: {
            combo_result.text = comboBox.textAt(comboBox.currentIndex)
        }
    }
    Text {
        Layout.alignment: Qt.AlignCenter
        id : combo_result
        text : "choose from combo"
    }

    }

}


```

--

## Text Input

- There are many different ways to input text
  - Line Edits allow single line entry
  - Text Areas for larger text entry
- Can also include Rich / Formatted text
- Validation can be part of the process (via regex for example)
- Can also use masks to hide passwords etc
- Note no web demos for this as they were problematic

--

## Numeric Input

- The main numeric inputs are spin-boxes these are usually int or double values
- Qt also has sliders and dials to do similar things
- Sliders work well but take up screen space, dials can be confusing in some cases
  - Houdini has some great methods for nudging values in better ranges

--

## Numeric Input

<iframe scrolling="auto" width="640"  height="400" src="./Numbers/Numbers.html" title="Numbers"></iframe>

```
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Numbers")
    GridLayout
    {
       anchors.fill: parent
       rows:   6
       columns:   2
        SpinBox {
            Layout.row : 0
            Layout.column: 0
            id: spinBox
        }
        SpinBox {

            Layout.row : 0
            Layout.column: 1

            id: spinbox2
            from: 0
            value: 110
            to: 100 * 100
            stepSize: 100
            property int decimals: 2
            property real realValue: value / 100

            validator: DoubleValidator {
                bottom: Math.min(spinbox2.from, spinbox2.to)
                top:  Math.max(spinbox2.from, spinbox2.to)
            }

            textFromValue: function(value, locale) {
                return Number(value / 100).toLocaleString(locale, 'f', spinbox2.decimals)
            }

            valueFromText: function(text, locale) {
                return Number.fromLocaleString(locale, text) * 100
            }
        }

        Dial {
            id: dial
            Layout.row: 2
            Layout.column: 0

        }
        Dial {
            id: dial2
            Layout.row: 2
            Layout.column: 1

        }



    RangeSlider {
        id: rangeSlider
        x: 69
        y: 438
        first.value: 0.25
        second.value: 0.75
    }

    Slider {
        id: slider
        x: 368
        y: 423
        value: 0.5
    }

  }

}

```

--

## Layouts
- Layouts are an important part of GUI design as they are responsible for the resizing of all widgets
  - Laying out is a complex process and need a lot of attention to get it working
- Qt provides 4 basic layouts 
  - Vertical / Horizontal
  - Form
  - Grid


--

## Containers

- Container widgets provide high level control over groups of objects on a form
- They can be used to perform a variety of functions such as 
  - managing input widgets
  - paged and tabbed layouts
  - decorative containers for other objects
- Typically 

--

## Containers

<iframe scrolling="auto" width="640"  height="400" src="./Containers/Containers.html" title="Numbers"></iframe>

--

## Items

- Items are usually based on the Qt [Model / View](https://doc.qt.io/qt-5/model-view-programming.html) paradigm
- Items are very useful for displaying data from SQL Queries / databases (we will do this in the labs)
- Typical views are 
  - tree
  - list
  - table 

---

# References

- [The Essential Guide to User Interface Design: An Introduction to GUI Design Principles and Techniques, Third Edition ](https://learning.oreilly.com/library/view/the-essential-guide/9780470053423/00_title.html)






