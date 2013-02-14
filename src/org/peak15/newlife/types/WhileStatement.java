package org.peak15.newlife.types;

public final class WhileStatement implements Statement {

	private final Condition condition;
	private final BlockStatement body;
	
	/**
	 * Construct a while statement.
	 * 
	 * @param condition to execute body while true.
	 * @param body block to execute while true.
	 */
	public WhileStatement(Condition condition, BlockStatement body) {
		if(condition == null || body == null) {
			throw new NullPointerException("WhileStatement needs a condition and body.");
		}
		
		this.condition = condition;
		this.body = body;
	}
	
	public Condition getCondition() {
		return this.condition;
	}
	
	public BlockStatement getBody() {
		return this.body;
	}
}
