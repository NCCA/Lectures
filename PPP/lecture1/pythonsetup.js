// output functions are configurable.  This one just appends some text
// to a pre element.

var editor;


function addCodeMirror(textID){
    editor = CodeMirror.fromTextArea(textID, {
    mode: "python",
    lineNumbers: true,
    theme : "monokai",



  });
  editor.setSize(800, 250);

}


function getCodeMirrorText(textID){
return editor.getValue();
}



function builtinRead(x) {
    if (Sk.builtinFiles === undefined || Sk.builtinFiles["files"][x] === undefined)
            throw "File not found: '" + x + "'";
    return Sk.builtinFiles["files"][x];
}

// Here's everything you need to run a python program in skulpt
// grab the code from your textarea
// get a reference to your pre element for output
// configure the output function
// call Sk.importMainWithBody()
function runit( code,  out) { 

  var prog = getCodeMirrorText(); //document.getElementById(code).value; 
  var mypre = document.getElementById(out); 
  function outf(text) { 
    var mypre = document.getElementById(out); 
    mypre.innerHTML = mypre.innerHTML + text; 
} 
  
  
  mypre.innerHTML = ''; 
   
   Sk.pre = out;
   Sk.configure({output:outf, read:builtinRead}); 
   (Sk.TurtleGraphics || (Sk.TurtleGraphics = {})).target = 'mycanvas';
   var myPromise = Sk.misceval.asyncToPromise(function() {
       return Sk.importMainWithBody("<stdin>", false, prog, true);
   });

   myPromise.then(function(mod) {
       console.log('success');
   },
       function(err) {
       console.log(err.toString());
       var mypre = document.getElementById("helloWorldOut");
       mypre.innerHTML = mypre.innerHTML + err.toString();

   });
} 
