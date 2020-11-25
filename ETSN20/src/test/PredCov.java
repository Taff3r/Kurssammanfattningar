package test;
import static org.junit.jupiter.api.Assertions.*;
import classes.NextDate;
import org.junit.jupiter.api.Test;

class PredCov {
	private NextDate d = new NextDate(0,1,12);
	private static final String INV_DATE = "Invalid Input Date";
	@Test
	public void pred1_invalid_input() {
		assertEquals("invalid Input Date",d.run(0, 4, 2000));
	}
	
	
	@Test
	public void pred2_30thOf31DayMonth() {
		assertEquals("7/31/2000",d.run(7, 30, 2000));
	}
	
	@Test
	public void pred3_31thOf31DayMonth() {
		assertEquals("8/1/2000",d.run(7, 31, 2000));
	}
	
	@Test
	public void pred4_29thOf30DayMonth() {
		assertEquals("6/30/2000",d.run(6, 29, 2000));
	}
	
	@Test
	public void pred5_30thOf30DayMonth() {
		assertEquals("7/1/2000",d.run(6, 30, 2000));
	}
	
	@Test
	public void pred6_toLargeDay() {
		assertEquals(INV_DATE, d.run(3, 45, 2000));
	}
	
	@Test
	public void pred7_30thOfDec() {
		assertEquals("12/31/2000", d.run(12, 30, 2000));
	}
	
	@Test
	public void pred8_toLargeDateDec() {
		assertEquals(INV_DATE, d.run(12, 32, 2000));
	}
	
	@Test
	public void pred9_lastOfDec() {
		assertEquals("1/1/2001", d.run(12, 31, 2000));
	}
	
	@Test
	public void pred10_27thOfFeb() {
		assertEquals("2/28/1999", d.run(2, 27, 1999));
	}
	
	@Test
	public void pred11_28thOfFebNonLeap() {
		assertEquals("3/1/1999", d.run(2, 28, 1999));
	}
	
	@Test
	public void pred12_28thOfFebLeap() {
		assertEquals("2/29/2000", d.run(2, 28, 2020));
	}
	
	@Test
	public void pred13_28thOfFebLeap() {
		assertEquals("2/29/2000", d.run(2, 28, 2020));
	}
	
	@Test
	public void pred14_29thOfFebNonLeap() {
		assertEquals(INV_DATE, d.run(2, 29, 1999));
	}
	
	@Test
	public void pred15_29thOfFebLeap() {
		assertEquals(INV_DATE, d.run(2, 29, 2020));
	}
	
	@Test
	public void pred16_toLargeDateFeb() {
		assertEquals(INV_DATE, d.run(2, 30, 1999));
	}

	/* ---- 90% STMT COV ABOVE ----*/
	@Test
	public void pred17_toManyDays30() {
		assertEquals(INV_DATE, d.run(4, 31, 2000));
	}
	
	@Test
	public void pred18_toLargeYearFlip() {
		assertEquals("Invalid Next Year", d.run(12, 32, 2021));
	}
	
	@Test
	public void pred19_flip31thDay() {
		assertEquals("1/31/2000", d.run(1, 30, 2000));
	}
	
	@Test
	public void pred20_toSmallDay() {
		assertEquals("invalid Input Date", d.run(1, 0, 2000));
	}
	
	@Test
	public void pred21_toSmallYear() {
		assertEquals("invalid Input Date", d.run(1, 1, 1800));
	}
	
	@Test
	public void pred22_toLargeYear() {
		assertEquals("invalid Input Date", d.run(1, 1, 2022));
	}
	
	@Test
	public void pred23_toLargeMonth() {
		assertEquals("invalid Input Date", d.run(13, 1, 2022));
	}
}
