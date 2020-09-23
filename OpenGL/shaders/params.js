{ tabColor: "#a00", editorTheme: "dark",
meshes: [
		{ type: "plane", name: "Plane", scale: 0.0001,doubleSided: true},
		{ type: "teapot", name: "Teapot", scale: 0.0001,doubleSided: true},
		{ type: "sphere", name: "Sphere",scale: 0.0001},
		{ type: "torus", name: "Torus",scale: 0.0001},
		{ type: "cylinder", name: "Cylinder",scale: 0.0001},
		{ type: "cube", name: "Cube",scale: 0.0001}
	],
  vertexShader : 
`
uniform float rotation;
void main()
{
  float r=radians(rotation);
   mat3 rot = mat3(
        vec3( cos(r),  sin(r),  0.0),
        vec3(-sin(r),  cos(r),  0.0),
        vec3( 0.0,         0.0,  1.0)
    );

mat3 scale = mat3(
        vec3(0.01,  0.0,  0.0),
        vec3(0.0,  0.01,  0.0),
        vec3(0.0,  0.0,  0.01)
    );

    gl_Position =  vec4( scale* rot * position.xyz, 1.0);
}
`, 

fragmentShader :
`
void main() 
{
	gl_FragColor = vec4(1.0,0.0,0.0, 1.0);
}
`,

uniforms: [
  { 
    type: "float", 
    value: 0.0, 
    min: 0.0, 
    max: 360.0, 
    name: "rotation",
    GUIName: "rotation"
  }
]

}