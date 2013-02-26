package org.peak15.newlife;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import org.peak15.newlife.types.Program;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.Type;
import org.peak15.newlife.types.Sequence;
import org.peak15.newlife.types.statement.CallStatement;
import org.peak15.newlife.types.statement.IfElseStatement;
import org.peak15.newlife.types.statement.Statement;
import org.peak15.newlife.types.statement.WhileStatement;

/**
 * Parses tokens into abstract statements and programs.
 * 
 * @throws ParserException in the event of a parsing error.
 * @throws InvalidSyntaxException upon encountering invalid syntax.
 * @throws NullPointerException if null is passed for any parameter,
 */
public final class Parser {
	
	private Parser() {}
	
	/**
	 * Parse an instruction call, IF(ELSE), or WHILE statement.
	 * Can not parse blocks.
	 * Parses precisely the tokens which form the statement, and no more.
	 * 
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed statement
	 */
	public static Statement parseStatement(Token first, Tokenizer tokenizer)
			throws ParserException, InvalidSyntaxException {
		
		if(first == null || tokenizer == null) {
			throw new NullPointerException("No paramenters may be null.");
		}
		
		Statement s = null;
		
		try {
			if(first.type() == Type.IDENTIFIER) {
				// CALL
				s = new CallStatement(first.text());
			}
			else if(first.text().equals("IF")) {
				// IF(ELSE)
				s = parseIf(first, tokenizer);
			}
			else if(first.text().equals("WHILE")) {
				// WHILE
				s = parseWhile(first, tokenizer);
			}
			else {
				assertCode(false, "Expected instruction call, IF, or WHILE.");
			}
		}
		catch(IOException e) {
			throw new ParserException("Read error while parsing statement.", e);
		}
		
		return s;
	}
	
	/**
	 * Parse a block.
	 * Parses precisely the tokens which form the block, and no more.
	 * 
	 * @param first the first token of the block, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed block
	 */
	public static Sequence<Statement> parseBlock(Token first, Tokenizer tokenizer)
			throws ParserException, InvalidSyntaxException {
		
		if(first == null || tokenizer == null) {
			throw new NullPointerException("No paramenters may be null.");
		}
		
		Sequence<Statement> s;
		
		try {
			Token t = first;
			Sequence.Builder<Statement> bb = new Sequence.Builder<>();
			
			while(isPrimitiveStatement(t)) {
				bb.append(parseStatement(t, tokenizer));
				
				// if the next token is part of the block, pull it out
				if(isPrimitiveStatement(tokenizer.peekNextToken())) {
					t = tokenizer.nextToken();
				}
				else {
					t = tokenizer.peekNextToken();
				}
			}
			
			s = bb.build();
		} catch(IOException e) {
			throw new ParserException("Read error while parsing block.", e);
		}
		
		return s;
	}
	
	/**
	 * Parse a program.
	 * Parses precisely the tokens which form the program, and no more.
	 * 
	 * @param first the first token of the program, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed program
	 */
	public static Program parseProgram(Token first, Tokenizer tokenizer)
			throws ParserException, InvalidSyntaxException {
		
		String name;
		Map<String, Sequence<Statement>> context = new HashMap<>();
		Sequence<Statement> body;
		Token t = first;
		
		try {
			// PROGRAM
			assertCode(t.text().equals("PROGRAM"),
					"Expected program to begin with \"PROGRAM\"");
			
			// program name
			t = tokenizer.nextToken();
			assertCode(t.type() == Type.IDENTIFIER,
					"Expected valid identifier for program name.");
			name = t.text();
			
			// IS
			t = tokenizer.nextToken();
			assertCode(t.text().equals("IS"),
					"Expected \"IS\" to follow program name.");
			
			// parse instructions (if any)
			t = tokenizer.nextToken(); // this could be BEGIN
			
			// go until we reach BEGIN
			while(!t.text().equals("BEGIN")) {
				assertCode(t.text().equals("INSTRUCTION"), "Malformed instruction definition.");
				
				NamedStatementSequence pair = parseInstruction(tokenizer, context.keySet());
				context.put(pair.name, pair.seq);
				
				// get next token (next instruction or BEGIN)
				t = tokenizer.nextToken();
			}
			
			// BEGIN
			assertCode(t.text().equals("BEGIN"),
					"Expected \"BEGIN\" after possible instruction definitions.");
			
			
			// parse body and add to program
			t = tokenizer.nextToken();
			body = parseBlock(t, tokenizer);
			
			// END
			t = tokenizer.nextToken();
			assertCode(t.text().equals("END"),
					"Expected \"END\" to follow program body.");
			
			// name again
			t = tokenizer.nextToken();
			assertCode(t.text().equals(name),
					"Expected program name to follow entire program.");
			
		} catch(IOException e) {
			throw new ParserException("Read error while parsing program.", e);
		}
		
		return new Program(name, context, body);
	}
	
	/**
	 * @param t token to test
	 * @return true if the blargStatement represented by the token is
	 *         an instruction call, IF(ELSE), or WHILE blargStatement.
	 */
	private static boolean isPrimitiveStatement(Token t) {
		return t.type() == Type.IDENTIFIER
				|| t.text().equals("IF")
				|| t.text().equals("WHILE");
	}

	/**
	 * Parses an instruction definition into a named block statement.
	 * 
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @param takenNames instruction names that have already been used.
	 * @return pair of the name and the block of the parsed instruction
	 */
	private static NamedStatementSequence parseInstruction (
			Tokenizer tokenizer,
			Set<String> takenNames)
			throws IOException, ParserException, InvalidSyntaxException {
		
		// instruction name
		Token t = tokenizer.nextToken();
		String instName = t.text();
		assertCode(t.type() == Type.IDENTIFIER,
				"Expected valid identifier for instruction name.");
		assertCode(!takenNames.contains(instName),
				"Expected a unique instruction name (a name was repeated).");
		
		// IS
		t = tokenizer.nextToken();
		assertCode(t.text().equals("IS"),
				"Expected \"IS\" to follow instruction name.");
		
		// body
		t = tokenizer.nextToken();
		Sequence<Statement> s = parseBlock(t, tokenizer);
		
		// END
		t = tokenizer.nextToken();
		assertCode(t.text().equals("END"),
				"Expected \"END\" to follow instruction body.");
		
		// name again
		t = tokenizer.nextToken();
		assertCode(t.text().equals(instName),
				"Expected instruction name to follow instruction definition.");
		
		return new NamedStatementSequence(instName, s);
	}

	/**
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return parsed IF(ELSE) blargStatement
	 */
	private static IfElseStatement parseIf(Token first, Tokenizer tokenizer)
			throws IOException, InvalidSyntaxException, ParserException {
		
		// condition
		Token t = tokenizer.nextToken();
		assertCode(t.type() == Type.CONDITION, "Expected condition after IF.");
		
		Condition condition = Condition.parseConditionString(t.text());
		
		// THEN
		t = tokenizer.nextToken();
		assertCode(t.text().equals("THEN"), "Expected \"THEN\" after IF condition.");
		
		// body
		t = tokenizer.nextToken();
		Sequence<Statement> body = parseBlock(t, tokenizer);
		
		// END or ELSE
		t = tokenizer.nextToken();
		assertCode(t.text().equals("END") || t.text().equals("ELSE"), "Expected \"END\" or \"ELSE\" after IF body.");
		
		IfElseStatement ret;
		if(t.text().equals("ELSE")) {
			t = tokenizer.nextToken();
			Sequence<Statement> elseBody = parseBlock(t, tokenizer);
			
			// END
			t = tokenizer.nextToken();
			assertCode(t.text().equals("END"), "Expected \"END\" after ELSE body.");
			
			ret = new IfElseStatement(condition, body, elseBody);
		}
		else { // if END
			ret = new IfElseStatement(condition, body);
		}
		
		// IF
		t = tokenizer.nextToken();
		assertCode(t.text().equals("IF"), "Expected \"IF\" after END.");
		
		return ret;
	}
	
	/**
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return parsed WHILE statement
	 * @throws InvalidSyntaxException 
	 * @throws IOException 
	 * @throws ParserException 
	 */
	private static WhileStatement parseWhile(Token first, Tokenizer tokenizer)
			throws InvalidSyntaxException, IOException, ParserException {
	
			// condition
			Token t = tokenizer.nextToken();
			assertCode(t.type() == Type.CONDITION, "Expected condition after IF.");
			
			Condition condition = Condition.parseConditionString(t.text());
			
			// DO
			t = tokenizer.nextToken();
			assertCode(t.text().equals("DO"), "Expected \"DO\" after WHILE condition.");
			
			// body
			t = tokenizer.nextToken();
			Sequence<Statement> body = parseBlock(t, tokenizer);
			
			// END WHILE
			String e = tokenizer.nextToken().text();
			String w = tokenizer.nextToken().text();
			assertCode(e.equals("END") && w.equals("WHILE"), "Expected \"END WHILE\" after WHILE body.");
			
			return new WhileStatement(condition, body);
	}
	
	/**
	 * Checks the specified condition, and throws an exception if it is false.
	 * 
	 * @param expectedTrueCond condition expected to be true
	 * @param failMsg Message to print if the condition is false.
	 * @throws InvalidSyntaxException If the condition is false.
	 */
	private static void assertCode(boolean expectedTrueCond, String failMsg)
			throws InvalidSyntaxException {
		
		if(!expectedTrueCond) {
			throw new InvalidSyntaxException(failMsg);
		}
	}
	
	/**
	 * For use in passing pairs for the context.
	 */
	private final static class NamedStatementSequence {
		public final String name;
		public final Sequence<Statement> seq;
		
		public NamedStatementSequence(String name, Sequence<Statement> seq) {
			this.name = name;
			this.seq = seq;
		}
	}
	
	/**
	 * Thrown by the parser upon encountering general errors.
	 */
	public static class ParserException extends Exception {
		private static final long serialVersionUID = -6370749099024552486L;

		public ParserException(String message) {
			super(message);
		}
		
		public ParserException(String message, Throwable e) {
			super(message, e);
		}
		
		public ParserException(Throwable e) {
			super(e);
		}
	}
	
	/**
	 * Thrown by the parser upon encountering invalid syntax.
	 */
	public static class InvalidSyntaxException extends Exception {
		private static final long serialVersionUID = 1755175877027285406L;

		public InvalidSyntaxException(String message) {
			super(message);
		}
		
		public InvalidSyntaxException(String message, Throwable e) {
			super(message, e);
		}
		
		public InvalidSyntaxException(Throwable e) {
			super(e);
		}
	}
}
