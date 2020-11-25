package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.Before;
import org.junit.jupiter.api.Test;

import classes.Triangle;

class Blackbox {

	/*
	 * getArea()
	 * Eq classes:
	 * 	C1: Output double 
	 * 	C2: Output -1.0
	 * 	C3: Input Triangle with positive integer sides
	 * 	C4: Input Triangle object with non-positive integer sides
	 */
	
	@Test
	void getAreaValid() {
		assertEquals(6, new Triangle(4,3,5).getArea());
	}
	
	@Test
	void getAreaInvalid() {
		assertEquals(-1.0, new Triangle(-4,3,5).getArea());
	}
	
	/* Boundrary Tests */
	@Test
	void getAreaLowerBound() {
		assertEquals(new Triangle(0,2,3).getArea(), -1);
	}
	
	
	/*
	 * getPerimeter()
	 * Eq classes:
	 * 	C1: Output int 
	 * 	C2: Output -1
	 * 	C3: Input Triangle with positive integer sides
	 * 	C4: Input Triangle object with non-positive integer sides
	 */
	
	@Test
	void getPerimeterValid() {
		assertEquals(12, new Triangle(4,3,5).getPerimeter());
	}
	
	@Test
	void getPerimeterInvalid() {
		assertEquals(-1, new Triangle(-4,3,5).getPerimeter());
	}
	
	/* Boundrary Tests */
	@Test
	void getPerimeterLowerbound() {
		assertEquals(-1, new Triangle(0,2,3).getPerimeter());
	}
	
	
	/*
	 * isIsosceles()
	 * Eq classes:
	 * 	C1: Output true 
	 * 	C2: Output false 
	 * 	C3: Input Triangle at least two sides that are equal and has positive integer sides
	 * 	C4: Input Triangle at least two sides that are not equal.
	 * 	C5: Input Triangle with at least one non-positive intger side.
	 */
	
	@Test
	void isIsosceles() {
		assertEquals(true, new Triangle(4,3,4).isIsosceles());
	}
	
	@Test
	void isIsocelesInvalid() {
		assertEquals(false, new Triangle(-4,3,-4).isIsosceles());
	}
	
	@Test
	void isIsocelesInvalid2() {
		assertEquals(false, new Triangle(4,3,5).isIsosceles());
	}
	
	/* Boundrary Tests */
	@Test
	void isIsoscelesLowerBound() {
		assertEquals(false, new Triangle(0,2,0).isIsosceles());
	}
	
	/*
	 * isEquilateral()
	 * Eq classes:
	 * 	C1: Output true 
	 * 	C2: Output false 
	 * 	C3: Input Triangle all sides that are equal and has positive integer sides
	 * 	C4: Input Triangle at least one side that is not equal to the others.
	 * 	C5: Input Triangle with at least one non-positive side.
	 */
	
	@Test
	void isEquilateralValid() {
		assertEquals(true, new Triangle(4,4,4).isEquilateral());
	}
	
	@Test
	void isEquilateral() {
		assertEquals(false, new Triangle(4,4,2).isEquilateral());
	}
	
	@Test
	void isEquilateralInvalid2() {
		assertEquals(false, new Triangle(-1,1,-1).isEquilateral());
	}
	
	/* Boundrary Tests */
	@Test
	void isEquilateralLowerBound() {
		assertEquals(false, new Triangle(0,0,0).isEquilateral());
	}
	
	/*
	 * isScalene()
	 * Eq classes:
	 * 	C1: Output true 
	 * 	C2: Output false 
	 * 	C3: Input Triangle all sides that are unequal and has positive integer sides
	 * 	C4: Input Triangle at least one side that is equal to the others.
	 * 	C5: Input Triangle with at least one non-positive side.
	 */
	
	@Test
	void isScaleneValid() {
		assertEquals(true, new Triangle(6,8,10).isScalene());
	}
	
	@Test
	void isScaleneInvalid() {
		assertEquals(false, new Triangle(4,4,2).isScalene());
	}
	
	@Test
	void isScaleneInvalid2() {
		assertEquals(false, new Triangle(-1,1,2).isScalene());
	}
	
	/* Boundrary Tests */
	@Test
	void isScaleneLowerbound() {
		assertEquals(false, new Triangle(0,1,2).isScalene());
	}
	
	/*
	 * isImpossible()
	 * Eq classes:
	 * 	C1: Output true 
	 * 	C2: Output false 
	 * 	C3: Input Triangle with sides that cannot form a triangle.
	 * 	C4: Input Triangle with sides that can form a triangle. 
	 */
	
	@Test
	void isImpossibleValid() {
		assertEquals(true, new Triangle(10,1,3).isImpossible());
	}
	
	@Test
	void isImpossibleInvalid() {
		assertEquals(false, new Triangle(5,4,4).isImpossible());
	}
	
	/* Boundrary Tests */
	@Test
	void isImpossibleLowerbound() {
		assertEquals(true, new Triangle(0,1,2).isImpossible());
	}
	
	/*
	 * isRightAngled()
	 * Eq classes:
	 * 	C1: Output true 
	 * 	C2: Output false 
	 * 	C3: Input Triangle with sides that can form a right-angled triangle.
	 * 	C4: Input Triangle with sides that cannot form a right-angled triangle. 
	 * 	C5: Input Triangle with sides that are negative. 
	 */
	
	@Test
	void isRightAngValid() {
		assertEquals(true, new Triangle(4,3,5).isRightAngled());
	}
	
	@Test
	void isRightAngInvalid() {
		assertEquals(false, new Triangle(5,4,4).isRightAngled());
	}
	
	@Test
	void isRightAngInvalid2() {
		assertEquals(false, new Triangle(-4,3,5).isRightAngled());
	}
	

	/* Boundrary Tests */
	@Test
	void isRightAngLowerbound() {
		assertEquals(false, new Triangle(0,0,0).isRightAngled());
	}
	
	/*
	 * classify()
	 * Eq classes:
	 * 	C1: Output "impossible" 
	 * 	C2: Output "isosceles" 
	 * 	C3: Output "scalene" 
	 * 	C4: Output "right-angled" 
	 * 	C5: Output "equilateral" 
	 * 	C6: Input Triangle with object forming an impossible triangle.
	 * 	C7: Input Triangle with object forming an isosceles triangle.
	 * 	C8: Input Triangle with object forming a scalene triangle.
	 * 	C9: Input Triangle with object forming a right-angled triangle.
	 * 	C10: Input Triangle with object forming an equilateral triangle.
	 */
	
	@Test
	void classifyImpossible() {
		assertEquals("impossible", new Triangle(10,1,3).classify());
	}
	
	@Test
	void classifyIsosceles() {
		assertEquals("isosceles", new Triangle(5,4,5).classify());
	}
	
	@Test
	void classifyScalene() {
		assertEquals("scalene", new Triangle(7,8,10).classify());
	}
	
	@Test
	void classifyRightAng() {
		assertEquals("right-angled", new Triangle(4,3,5).classify());
	}
	
	@Test
	void classifyEquilateral() {
		assertEquals("equilateral", new Triangle(4,4,4).classify());
	}
	
	/* Boundrary Tests */
	@Test
	void classifyLowerbound() {
		assertEquals("impossible", new Triangle(0,1,2).classify());
	}
	
	/*
	 * getSideLengths()
	 * Eq classes:
	 * 	C1: Output String, comma-seperated list of the sides 
	 * 	C2: Input a Triangle object. 
	 */
	
	@Test
	void getSideLengths() {
		Triangle tri = new Triangle(1,1,1);
		assertEquals("1,1,1", tri.getSideLengths());
	}
	
	@Test
	void getSideLengthsLowerBound() {
		assertEquals("0,0,0", new Triangle(0,0,0).getSideLengths());
	}
	
	/*
	 * setSideLengths(int,int,int)
	 * Eq classes:
	 * 	C1: Output Triangle reference same as the one which the sides were set on. 
	 * 	C2: Input int, int, int: the sides to be set. 
	 */
	
	@Test
	void setSideLengths() {
		Triangle tri = new Triangle(1,1,1);
		assertEquals(tri, tri.setSideLengths(2,2,2));
	}
	@Test
	void setSideLengthsBoundrary() {
		Triangle tri = new Triangle(1,1,1);
		assertEquals(tri, tri.setSideLengths(0,2,2));
	}
}
