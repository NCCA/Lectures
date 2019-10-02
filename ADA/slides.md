# ADA
## ```Algorithms + Data Structures == Animation```

### [Jon Macey](https://nccastaff.bournemouth.ac.uk/jmacey/)
### National Center for Computer Animation
### Bournemouth University

---

## About me

- My first computer was a Texas Instruments Ti 99 (followed by a Vic 20 then a PC)
- Been programming since 1979!
- Did a degree in Electronics, then MSc in Computer Animation
- Teach programming and Maths to Animators.

<img src="images/computers.png" width="60%">


---

## Can you see any programming?
  <video controls>
    <source data-src="video/showreel.mp4" type="video/mp4" />
  </video>


---


## Thinking like a programmer

- Most programming task require you to think in a certain way
  - Algorithms (how to do a task)
  - Data Structures (how we repesetent things)
- This "computational thinking" approach can be applied to many areas.

--

## Sequences

<a href="examples/sequence/index.html" target="popup" onclick="popupWindow('examples/sequence/index.html','sequence',400,300)">Demo</a>


```
drawRed();
drawGreen();
drawBlue();
```

--

## [Selection](examples/selection/index.html)

<a href="examples/selection/index.html" target="popup" onclick="popupWindow('examples/selection/index.html','selection',520,580);">Demo</a>


```
if(keyUpPressed())
  moveUp();
else if(keyDownPressed())
  moveDown();
else if(keyLeftPressed())
  moveLeft();
else if(keyRightPressed())
  moveRight();  
```

--

## Iteration


<a href="examples/iteration/index.html" target="popup" onclick="popupWindow('examples/iteration/index.html','Iteration',520,580);">Demo</a>

```
while(true)
{
  for_each(particle p)
  {
    p.update();
    p.draw();
  }
}
```