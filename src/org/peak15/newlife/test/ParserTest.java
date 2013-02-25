package org.peak15.newlife.test;

import static org.junit.Assert.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import org.junit.Test;
import org.peak15.newlife.Condition;
import org.peak15.newlife.Parser;
import org.peak15.newlife.Tokenizer;
import org.peak15.newlife.Parser.InvalidSyntaxException;
import org.peak15.newlife.Parser.ParserException;
import org.peak15.newlife.types.Program;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.statement.BlockStatement;
import org.peak15.newlife.types.statement.CallStatement;
import org.peak15.newlife.types.statement.IfElseStatement;
import org.peak15.newlife.types.statement.Statement;
import org.peak15.newlife.types.statement.WhileStatement;

public class ParserTest {

	@Test
	public void testParseStatement() {
		try {
			InputStream testFile = ParserTest.class.getResourceAsStream("test-statement.nl");
			Tokenizer tokenizer = new Tokenizer(new BufferedReader(new InputStreamReader(testFile)));
			
			// prime the tokenizer
			Token token = tokenizer.nextToken();
			
			// parse!
			Statement s = Parser.parseStatement(token, tokenizer);
			System.out.println(s);
			
			// check if-else statement from file
			assertTrue(s instanceof IfElseStatement);
			
			IfElseStatement ifElse = (IfElseStatement) s;
			assertEquals(Condition.RANDOM, ifElse.condition());
			
			// untyped statement from else block
			s = ifElse.elseBody().get(0);
			
			// cast to call
			CallStatement call = (CallStatement) s;
			assertEquals("infect", call.instructionName());
			
		} catch(IOException | ParserException | InvalidSyntaxException e) {
			e.printStackTrace();
			fail(e.getMessage());
		}
	}

	@Test
	public void testParseBlock() {
		try {
			InputStream testFile = ParserTest.class.getResourceAsStream("test-block.nl");
			Tokenizer tokenizer = new Tokenizer(new BufferedReader(new InputStreamReader(testFile)));
			
			// prime the tokenizer
			Token token = tokenizer.nextToken();
			
			// parse!
			BlockStatement b = Parser.parseBlock(token, tokenizer);
			System.out.println(b);
			
			assertEquals(4, b.size());
			
			assertTrue(b.get(2) instanceof WhileStatement);
		}
		catch(IOException | ParserException | InvalidSyntaxException e) {
			e.printStackTrace();
			fail(e.getMessage());
		}
	}

	@Test
	public void testParseProgram() {
		try {
			InputStream testFile = ParserTest.class.getResourceAsStream("test-program.nl");
			Tokenizer tokenizer = new Tokenizer(new BufferedReader(new InputStreamReader(testFile)));
			
			// prime the tokenizer
			Token token = tokenizer.nextToken();
			
			// parse!
			Program p = Parser.parseProgram(token, tokenizer);
			System.out.println(p);
			
			assertEquals("SteerClear", p.name());
			
			assertTrue(p.context().containsKey("StepAside"));
			
			assertEquals(1, p.body().size());
		}
		catch(IOException | ParserException | InvalidSyntaxException e) {
			e.printStackTrace();
			fail(e.getMessage());
		}
	}
}
