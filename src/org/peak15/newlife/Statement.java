package org.peak15.newlife;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

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
	 * 
	 * @param tokenizer The tokenizer to read from.
	 * @param block Is the statement to be parsed a block?
	 */
	public Statement(Tokenizer tokenizer, boolean parseBlock) {
		//TODO: Implement
		type = null;
		statements = null;
		condition = null;
		instruction = null;
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
