       if (typeof(Storage) === "undefined") {
                alert("Sorry this device is not capable of storing notes");
        }

    Reveal.initialize({
                        controls: true,
                        progress: false,
                        history: true,
                        center: false,
                        
                        slideNumber: 'c/t' ,
                        math: {
                        mathjax: 'https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.0/MathJax.js',
                        config: 'TeX-AMS_HTML-full'  // See http://docs.mathjax.org/en/latest/config-files.html
                        },
                       menu: {
									markers: true,
									openSlideNumber: true,
									keyboard: false,
										custom: [
										{ title: 'Code Style', icon: '<i class="fa fa-external-link">', src: '/jmacey/js/reveal.js/codeThemes.html' },
										]
			        
                                    },
            // Optional libraries used to extend on reveal.js
            dependencies: [
                            { src: '/jmacey/js/reveal.js/lib/js/classList.js', condition: function() { return !document.body.classList; } },
                            { src: '/jmacey/js/reveal.js/plugin/markdown/marked.js', condition: function() { return !!document.querySelector( '[data-markdown]' ); } },
                            { src: '/jmacey/js/reveal.js/plugin/markdown/markdown.js', condition: function() { return !!document.querySelector( '[data-markdown]' ); } },
                            { src: '/jmacey/js/reveal.js/plugin/highlight/highlight.js', async: true, callback: function() { hljs.initHighlightingOnLoad(); } },
                            { src: '/jmacey/js/reveal.js/plugin/math/math.js', async: true },
                            { src: '/jmacey/js/reveal.js/plugin/line-numbers/line-numbers.js'},
                            { src:'/jmacey/js/reveal.js/plugin/reveal-sampler/sampler.js' },
                            { src:'/jmacey/js/reveal.js/reveal.js-fullscreen-code.js' },
                            { src: '//cdn.jsdelivr.net/npm/reveal-plantuml' },
               
                        ],

    });
    var gCurrentSlide=0;
    Reveal.addEventListener( 'slidechanged', function( event ) {

		
  	var totalslides = document.querySelectorAll( '.reveal .slides section:not(.stack)' ).length;
  	var current_slide = 0;

  	var horizontal_slides = document.querySelectorAll( '.reveal .slides>section' );
  	for (var i = 0; i < event.indexh; i++)
		 {
    // get subslides
    	var subslides = horizontal_slides[i].querySelectorAll('section');

    // if subslides.length is 0, add 1 for horizontal slide, else add subslides.length
    	current_slide += (subslides.length === 0) ? 1 : subslides.length;
  	}

  	current_slide += event.indexv+1;
		gCurrentSlide=current_slide;
		console.log("slide "+gCurrentSlide);

    // event.previousSlide, event.currentSlide, event.indexh, event.indexv
} );

function loadCss(name){

var head = document.getElementsByTagName('head')[0],
   link = document.createElement('link');
   link.type = 'text/css';
   link.rel = 'stylesheet';
   link.href = "/jmacey/js/reveal.js/lib/css/"+name;
   head.appendChild(link);
    return link;
}



// 3. On Reveal.js ready event, copy header/footer <div> into each `.slide-background` <div>
var header = $('#header').html();
if ( window.location.search.match( /print-pdf/gi ) ) {
    Reveal.addEventListener( 'ready', function( event ) {
        $('.slide-background').append(header);
    });
}
else {
    $('div.reveal').append(header);
}

