package org.peak15.newlife;

import java.io.IOException;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import org.peak15.newlife.Token.TokenType;

import static org.peak15.newlife.NewLifeParserException.assertCode;

/**
 * One abstract statement of code.
 * 
 * Immutable.
 */
public final class Statement {
	public enum StatementType {
		BLOCK,
		IF,
		IF_ELSE,
		WHILE,
		CALL
	}
	
	public enum Condition {
		NEXT_IS_EMPTY,
		NEXT_IS_NOT_EMPTY,
		NEXT_IS_WALL,
		NEXT_IS_FRIEND,
		NEXT_IS_ENEMY,
		NEXT_IS_NOT_ENEMY,
		RANDOM,
		TRUE
	}
	
	private final StatementType type;
	private final List<Statement> statements;
	private final Condition condition;
	private final String instruction;
	
	/**
	 * Parse a statement from the given tokenizer.
	 * The first token should NOT have already been removed,
	 * and this will not remove a trailing token.
	 * This removes precisely the tokens which form the statement.
	 * 
	 * @param tokenizer The tokenizer to read from.
	 * @param block Is the statement to be parsed a block?
	 * @throws IOException if the parser fails to read
	 * @throws NewLifeParserException upon encountering a syntax error
	 */
	public Statement(Tokenizer tokenizer, boolean parseBlock) throws IOException, NewLifeParserException {
		Token t = tokenizer.nextToken();
		
		if(parseBlock) {
			this.type = StatementType.BLOCK;
			this.statements = new LinkedList<Statement>();
			this.condition = null;
			this.instruction = null;
			
			while(t.getType() == TokenType.IDENTIFIER
					|| t.getText().equals("IF")
					|| t.getText().equals("WHILE")) {
				
				this.statements.add(parseStatement(t, tokenizer));
			}
		}
		else {
			Statement s = parseStatement(t, tokenizer);
			
			this.type = s.getType();
			this.statements = s.getStatements();
			this.condition = s.getCondition();
			this.instruction = s.getInstruction();
		}
	}
	
	/**
	 * Parse an instruction call, IF(ELSE), or WHILE statement.
	 * Can not parse blocks.
	 * 
	 * @param firstToken the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed statement
	 */
	private static Statement parseStatement(Token firstToken, Tokenizer tokenizer) {
		if(firstToken.getType() == TokenType.IDENTIFIER) {
			//
		}
		else if(firstToken.getText().equals("IF")) {
			//
		}
		else { // WHILE
			//
		}
		
		return null;
	}
	
	/**
	 * Construct a BLOCK statement.
	 * 
	 * @param statements The statements in the block.
	 */
	public Statement(List<Statement> statements) {
		type = StatementType.BLOCK;
		this.statements = new LinkedList<Statement>(statements);
		this.condition = null;
		instruction = null;
	}
	
	/**
	 * Construct an IF statement.
	 * 
	 * @param cond condition for the statement
	 * @param body code for the statement
	 */
	public Statement(Condition cond, Statement body) {
		type = StatementType.IF;
		this.condition = cond;
		statements = Collections.singletonList(body);
		instruction = null;
	}
	
	/**
	 * Construct a CALL statement.
	 * 
	 * @param instruction
	 */
	public Statement(String instruction) {
		type = StatementType.CALL;
		this.instruction = instruction;
		condition = null;
		statements = null;
	}
	
	public StatementType getType() {
		return type;
	}
	
	public Condition getCondition() {
		return condition;
	}
	
	public String getInstruction() {
		return instruction;
	}
	
	public List<Statement> getStatements() {
		return Collections.unmodifiableList(statements);
	}
}
