# DOSE2 for Amiga Classic (+AMMX for Vampire accellerators)
This is an Amiga port of an old demo released on 2001 by Mfx. 

According to the author this demo does not feature any racism (with italians) and I agree with him. 

Since I am italian I took the liberty of porting the project to Classic Amiga. 

This is a quite demanding demo and I tried to target the Vampire platform taking advantage of libSDL+AMMX but should work also on emulated RTG Amigas (Winuae).

Demo link

https://www.pouet.net/prod.php?which=3289


# Screenshots

![alt text](https://content.pouet.net/files/screenshots/00003/00003289.png)

# Youtube links

https://www.youtube.com/watch?v=xOxqMY4ZwRk&t=6s

https://www.youtube.com/watch?v=JHGKR_NFnYw

# Lyrics

```
One day imma gona to Malta to bigga hotell
In the morning i go down to eat a breakfast
I tell the waitress i wanna 2 pisses of toast
She brings me only one piss
I tell her i wanna to piss
She says go to the toilet
I say you dont understand
I want to piss on my plate
She say you better no piss on the plate
You son of a bitch!
I dont even know the lady
And she calls me a son of a bitch

Later

I go to eat at a bigga resturant
The waitress bring me a spoon and
a knife, but no fork!
I tell her i wanna the fuck
She tellin me everyone wanna fuck
I tell her you dont understand
I wanna fucka on the table
She say you better not fuck on the table
You son of a bitch!
I dont even know the lady
And she calls me a son of a bitch

So i go back to my room in a hotel
And there is no sheeats on the bed
Call the manager and im tellin him i wanna shit!
He tellin me go to the toilet
I say you dont understand
I wanna shit on my bed!
He say you better not shit on my bed
You son of you bitch!

I go to the check out
and the man in the desk says
Peace on you, i said piss on you too
you son of a bitch!
Im goin back to Italia, Arrivederci
```

# Compiling
I usually take advantage of Docker + Bebbo gcc + Amigaport SDL 1.2 to port stuff to m68k:

```
   git clone https://github.com/Ozzyboshi/Amiga-Vampire-dose2.git
   docker run -it --rm -v $(pwd)/Amiga-Vampire-dose2:/data -w /data ozzyboshi/bebbo-amiga-gcc:20191224 bash -c 'make && make dist'
```

# Testing
Tested on:

- Vampire v600 core 2.11 - Coffin r52 (Ozzyboshi)
- Vampire v600 core 2.12RC3 - Coffin r55 (Dr Procton)

