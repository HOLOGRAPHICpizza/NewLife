package org.peak15.newlife.types;

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
	 * @param body code to execute if true
	 */
	public Statement(Condition cond, Statement body) {
		this.type = StatementType.IF;
		this.condition = cond;
		this.statements = Collections.singletonList(body);
		this.instruction = null;
	}
	
	/**
	 * Construct an IF_ELSE statement.
	 * 
	 * @param cond condition for the statement
	 * @param body code to execute if true
	 * @param elseBody code to execute if false
	 */
	public Statement(Condition cond, Statement body, Statement elseBody) {
		this.type = StatementType.IF_ELSE;
		this.condition = cond;
		this.instruction = null;
		
		this.statements = new LinkedList<Statement>();
		this.statements.add(body);
		this.statements.add(elseBody);
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
		if(statements == null)
			return null;
		
		return Collections.unmodifiableList(statements);
	}
}
