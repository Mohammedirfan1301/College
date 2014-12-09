I worked by myself on this extra credit project.
This program is a car dealership simulator. It has the following capabilities:

- You can use the base class as a generic dealership, allowing you to add cars, buy cars, and keep track of inventory.
- I made 3 derived classes which for the most part use all of the parent class's functions, except they allow sales to be run at certain dealerships. This means a "Ford" dealership can run a 20% sale, but Chrysler might only do a 5% sale this month.
- I used maps for representing the car model / price combinations. The car model acts as the key, while the price is the mapped value.

Pseudocode of main:

I basically declare objects of 4 different classes, in the following order:

1. Dealership Object
2. Ford Object
3. GM Object
4. Chrysler Object

After declaring an object, I test the output first, add a few cars, buy a car or two and test to make sure that after buying a car it is removed from the map. I then reprint out the inventory list for testing / showing off purposes.

I did not use any code from anyone other than myself. I did refer to past homework assignments for using maps, I also used cplusplus.com to find out how to remove from maps, and I looked up the prices of various cars on Ford/GM/Chrysler's websites.