function setupGui() 
{
	ctrls = 
	{
	roughnessScale : 0.8,
	exposure : 2.2,
	textureRepeatU : 0.6,
	textureRepeatV : 0.6,
	textureRotation : 0.0,
	l1 : 300.0,
	l2 : 300.0,
	l3 : 300.0,
	l4 : 300.0,
	ly : 2.0,
	lr : 2.0,
	texture : "greasy"

	};
	var h;

	var gui = new dat.GUI({autoPlace: true} );

	// material (color)
	gui.add(ctrls,"roughnessScale",0.0,1.0,0.01).name("roughnessScale").onChange(function(){needsUpdate=true; })
	gui.add(ctrls,'texture',{"greasy" : "greasy", "rusty" : "rusty", "panel" : "panel", "copper" : "copper","wood" : "wood"}).onChange(function(){ needsUpdate=true; })
	gui.add(ctrls,"textureRepeatU",0.0,10.0,0.1).name("Repeat U").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"textureRepeatV",0.0,10.0,0.1).name("Repeat V").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"textureRotation",0.0,360.0,1).name("texture rotation").onChange(function(){needsUpdate=true;})
	
	gui.add(ctrls,"exposure",0.0,3.0,0.1).name("exposure").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"ly",-10.0,10.0,0.1).name("Light y").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"lr",0.0,50.0,0.5).name("Light rad").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l1",0.0,900.0,10).name("Light 1 Power").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l2",0.0,900.0,10).name("Light 2 Power").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l3",0.0,900.0,10).name("Light 3 Power").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l4",0.0,900.0,10).name("Light 4 Power").onChange(function(){needsUpdate=true;})
	var customContainer = $('.moveGUI').append($(gui.domElement));

}