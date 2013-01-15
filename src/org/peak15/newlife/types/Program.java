package org.peak15.newlife.types;

import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import org.peak15.newlife.NewLifeParserException;
import org.peak15.newlife.Tokenizer;

import static org.peak15.newlife.types.Token.TokenType;

/**
 * One abstract program.
 * 
 * Immutable.
 */
public final class Program {
	private final String name;
	private final Map<String, Statement> context;
	private final Statement body;
	
	public Program(String name, Map<String, Statement> context, Statement body) {
		this.name = name;
		this.context = new HashMap<String, Statement>(context);
		this.body = body;
	}
	
	/**
	 * Parse a program from a tokenizer.
	 * The first token should NOT have already been removed,
	 * and this will not remove a trailing token.
	 * This removes precisely the tokens which form the program.
	 * 
	 * 
	 * @param tokenizer to parse from.
	 * @throws IOException if the tokenizer fails to read
	 */
	public Program(Tokenizer tokenizer) throws NewLifeParserException {
		this.context = new HashMap<String, Statement>();
		
		Token t;
		try {
			// PROGRAM
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("PROGRAM"),
					"Expected program to begin with \"PROGRAM\"");
			
			// program name
			t = tokenizer.nextToken();
			assertCode(t.getType() == TokenType.IDENTIFIER,
					"Expected valid identifier for program name.");
			this.name = t.getText();
			
			// IS
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("IS"),
					"Expected \"IS\" to follow program name.");
			
			// parse instructions (if any)
			t = tokenizer.nextToken(); // this could be BEGIN
			
			// go until we reach BEGIN
			while(!t.getText().equals("BEGIN")) {
				assertCode(t.getText().equals("INSTRUCTION"), "Malformed instruction definition.");
				
				NamedStatement pair = parseInstruction(tokenizer, context.keySet());
				this.context.put(pair.name, pair.statement);
				
				// get next token (next instruction or BEGIN)
				t = tokenizer.nextToken();
			}
			
			// BEGIN
			assertCode(t.getText().equals("BEGIN"),
					"Expected \"BEGIN\" after possible instruction definitions.");
			
			
			// parse body and add to program
			body = new Statement(tokenizer, true);
			
			// END
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("END"),
					"Expected \"END\" to follow program body.");
			
			// name again
			t = tokenizer.nextToken();
			assertCode(t.getText().equals(this.name),
					"Expected program name to follow entire program.");
			
		} catch(IOException e) {
			throw new NewLifeParserException("Read error while parsing program.", e);
		}
		
	}
	
	/**
	 * Parses an instruction from the tokenizer into a BLOCK statement.
	 * The first token should have already been removed.
	 * 
	 * @param tokenizer to parse from
	 * @param takenNames instruction names that have already been used.
	 * @return pair of the name and the block of the parsed instruction
	 * @throws IOException if the parser fails to read
	 * @throws NewLifeParserException upon encountering a syntax error
	 */
	private static NamedStatement parseInstruction(
			Tokenizer tokenizer,
			Set<String> takenNames)
			throws IOException, NewLifeParserException {
		
		Token t;
		
		// instruction name
		t = tokenizer.nextToken();
		String instName = t.getText();
		assertCode(t.getType() == TokenType.IDENTIFIER,
				"Expected valid identifier for instruction name.");
		assertCode(!takenNames.contains(instName),
				"Expected a unique instruction name (a name was repeated).");
		
		// IS
		t = tokenizer.nextToken();
		assertCode(t.getText().equals("IS"),
				"Expected \"IS\" to follow instruction name.");
		
		// body
		Statement s = new Statement(tokenizer, true);
		
		// END
		t = tokenizer.nextToken();
		assertCode(t.getText().equals("END"),
				"Expected \"END\" to follow instruction body.");
		
		// name again
		t = tokenizer.nextToken();
		assertCode(t.getText().equals(instName),
				"Expected instruction name to follow instruction definition.");
		
		return new NamedStatement(instName, s);
	}
	
	/**
	 * For use in passing pairs for the context.
	 * Apparently it is Java "best practice" to create a class for pairs.
	 */
	private static class NamedStatement {
		public final String name;
		public final Statement statement;
		
		public NamedStatement(String name, Statement statement) {
			this.name = name;
			this.statement = statement;
		}
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @return the context
	 */
	public Map<String, Statement> getContext() {
		return Collections.unmodifiableMap(context);
	}

	/**
	 * @return the body
	 */
	public Statement getBody() {
		return body;
	}
}
