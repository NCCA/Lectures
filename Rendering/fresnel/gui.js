function setupGui() 
{

	ctrls = 
	{
	albedor : 0.0,
	albedog : 0.0,
	albedob : 0.0,
	metallic : 0.5,
	roughness : 0.5,
	l1 : 300.0,
	l2 : 0.0,
	l3 : 4.0,
	l4 : 12.0,

	};
	var h;

	var gui = new dat.GUI({autoPlace: true} );

	// material (color)

	h = gui.addFolder( "albedo" );

	h.add( ctrls, "albedor", 0.0, 1.0, 0.1 ).name( "red" ).onChange( function(){ needsUpdate=true;  } );
	h.add( ctrls, "albedog", 0.0, 1.0, 0.1 ).name( "green" ).onChange( function(){ needsUpdate=true;  } );
	h.add( ctrls, "albedob", 0.0, 1.0, 0.1 ).name( "blue" ).onChange( function(){ needsUpdate=true;  } );
  
	gui.add(ctrls,"metallic",0.0,1.0,0.01).name("metallic").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"roughness",0.0,1.0,0.01).name("roughness").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l1",0.0,500.0,10).name("Light 1 Power").onChange(function(){needsUpdate=true;})
	
	gui.add(ctrls,"l2",-20.0,20.0,0.2).name("x pos").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l3",-20.0,20.0,0.2).name("y pos").onChange(function(){needsUpdate=true;})
	gui.add(ctrls,"l4",-20.0,20.0,0.2).name("z pos").onChange(function(){needsUpdate=true;})




	var customContainer = $('.moveGUI').append($(gui.domElement));

}