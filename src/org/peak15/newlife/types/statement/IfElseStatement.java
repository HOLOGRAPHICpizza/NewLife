package org.peak15.newlife.types.statement;

import org.peak15.newlife.Condition;
import org.peak15.newlife.types.Sequence;

public final class IfElseStatement implements Statement {

	private final Condition condition;
	private final Sequence<Statement> body, elseBody;
	
	/**
	 * Construct an if statement.
	 * 
	 * @param condition to execute body when true
	 * @param body block to execute when true.
	 */
	public IfElseStatement(Condition condition, Sequence<Statement> body) {
		this(condition, body, Sequence.<Statement>emptySequence());
	}
	
	/**
	 * Construct an if else statement.
	 * 
	 * @param condition to execute body when true, or elseBody when false.
	 * @param body block to execute when true.
	 * @param elseBody block to execute when false.
	 */
	public IfElseStatement(Condition condition, Sequence<Statement> body, Sequence<Statement> elseBody) {
		if(condition == null || body == null || elseBody == null) {
			throw new NullPointerException("No paramaters may be null.");
		}
		
		this.condition = condition;
		this.body = body;
		this.elseBody = elseBody;
	}
	
	public Condition condition() {
		return this.condition;
	}
	
	public Sequence<Statement> body() {
		return this.body;
	}
	
	public Sequence<Statement> elseBody() {
		return this.elseBody;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof IfElseStatement)) {
			return false;
		}
		
		IfElseStatement s = (IfElseStatement) obj;
		
		return	s.condition().equals(this.condition()) &&
				s.body().equals(this.body()) &&
				s.elseBody().equals(this.elseBody());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.condition().hashCode();
		result = 1327 * result + this.body().hashCode();
		result = 1327 * result + this.elseBody().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		String elseDesc = "";
		if(this.elseBody().size() > 0) {
			elseDesc = ", ELSE: " + this.elseBody().toString();
		}
		
		return String.format("(IF %s: %s%s)", this.condition(), this.body(), elseDesc);
	}
}
