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
