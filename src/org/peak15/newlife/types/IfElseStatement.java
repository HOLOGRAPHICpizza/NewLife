package org.peak15.newlife.types;

public final class IfElseStatement implements Statement {

	private final Condition condition;
	private final BlockStatement body, elseBody;
	
	/**
	 * Construct an if statement.
	 * 
	 * @param condition to execute body when true
	 * @param body
	 */
	public IfElseStatement(Condition condition, BlockStatement body) {
		this(condition, body, null);
	}
	
	/**
	 * Construct an if else statement.
	 * 
	 * @param condition to execute body when true, or elseBody (if present) when false.
	 * @param body block to execute when true.
	 * @param elseBody block to execute when false, or null for none.
	 */
	public IfElseStatement(Condition condition, BlockStatement body, BlockStatement elseBody) {
		if(condition == null || body == null) {
			throw new NullPointerException("IfElseStatement needs at least a condition and body.");
		}
		
		this.condition = condition;
		this.body = body;
		this.elseBody = elseBody;
	}
	
	public Condition getCondition() {
		return this.condition;
	}
	
	public BlockStatement getBody() {
		return this.body;
	}
	
	public BlockStatement getElseBody() {
		return this.elseBody;
	}
}
