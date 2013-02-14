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
	public static Statement makeBlock(List<Statement> statements) {
		return new Statement(
				StatementType.BLOCK,
				new LinkedList<Statement>(statements),
				null,
				null);
	}
	
	/**
	 * Construct an IF statement.
	 * 
	 * @param cond condition for the statement
	 * @param body code to execute if true
	 */
	public static Statement makeIf(Condition cond, Statement body) {
		if(cond == null || body == null) {
			throw new NullPointerException();
		}
		
		return new Statement(
				StatementType.IF,
				Collections.singletonList(body),
				cond,
				null);
	}
	
	/**
	 * Construct an IF_ELSE statement.
	 * 
	 * @param cond condition for the statement
	 * @param body code to execute if true
	 * @param elseBody code to execute if false
	 */
	public static Statement makeIfElse(Condition cond, Statement body, Statement elseBody) {
		if(cond == null || body == null || elseBody == null) {
			throw new NullPointerException();
		}
		
		List<Statement> statements = new LinkedList<>();
		statements.add(body);
		statements.add(elseBody);
		
		return new Statement(
				StatementType.IF_ELSE,
				statements,
				cond,
				null);
	}
	
	/**
	 * Construct a CALL statement.
	 * 
	 * @param instruction
	 */
	public static Statement makeCall(String instruction) {
		if(instruction == null) {
			throw new NullPointerException();
		}
		
		return new Statement(
				StatementType.CALL,
				null,
				null,
				instruction);
	}
	
	/**
	 * Construct a WHILE statement.
	 * 
	 * @param condition execute body while this is true
	 * @param body BLOCK statement to execute while condition holds
	 * @return WHILE statement with given components
	 */
	public static Statement makeWhile(Condition condition, Statement body) {
		if(condition == null || body == null) {
			throw new NullPointerException();
		}
		if(body.type != StatementType.BLOCK) {
			throw new IllegalArgumentException("body is not a BLOCK statement");
		}
		
		return new Statement(
				StatementType.WHILE,
				Collections.singletonList(body),
				condition,
				null);
	}
	
	private Statement(StatementType type, List<Statement> statements,
			Condition condition, String instruction) {
		this.type = type;
		this.statements = statements;
		this.condition = condition;
		this.instruction = instruction;
	}
	
	public StatementType getType() {
		return type;
	}
	
	/**
	 * Only valid for statements with conditions.
	 * 
	 * @return the condition
	 */
	public Condition getCondition() {
		switch(type) {
		case IF:
		case IF_ELSE:
		case WHILE:
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		
		return condition;
	}
	
	/**
	 * Only valid for CALL statements.
	 * 
	 * @return the call instruction
	 */
	public String getInstruction() {
		if(type != StatementType.CALL) {
			throw new UnsupportedOperationException();
		}
		
		return instruction;
	}
	
	/**
	 * For BLOCKs, the body of statements.
	 * For IF(_ELSE)s, the body, then the elseBody (if any).
	 * For WHILEs, the body of statements.
	 * 
	 * Invalid for other statement types.
	 * 
	 * @return the list of statements within this statement
	 */
	public List<Statement> getStatements() {
		switch(type) {
		case BLOCK:
		case IF:
		case IF_ELSE:
		case WHILE:
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		
		return Collections.unmodifiableList(statements);
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof Statement)) {
			return false;
		}
		
		Statement t = (Statement) obj;
		
		if(t.getType() != this.getType()) {
			return false;
		}
		
		switch(t.getType()) {
		case BLOCK:
			return t.getStatements().equals(this.getStatements());
			
		case CALL:
			return t.getInstruction().equals(this.getInstruction());
			
		case IF:
		case IF_ELSE:
		case WHILE:
			return	t.getCondition() == this.getCondition() &&
					t.getStatements().equals(this.getStatements());
		
		default:
			throw new UnsupportedOperationException();
		}
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		
		result = 1327 * result + this.getType().hashCode();
		
		switch(this.getType()) {
		case BLOCK:
			result = 1327 * result + this.getStatements().hashCode();
			break;
			
		case CALL:
			result = 1327 * result + this.getInstruction().hashCode();
			break;
			
		case IF:
		case IF_ELSE:
		case WHILE:
			result = 1327 * result + this.getCondition().hashCode();
			result = 1327 * result + this.getStatements().hashCode();
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		
		return result;
	}
	
	@Override
	public String toString() {
		StringBuilder desc = new StringBuilder();
		
		switch(this.getType()) {
		case BLOCK:
			desc.append(this.getStatements().size()).append(" statements");
			break;
			
		case CALL:
			desc.append(this.getInstruction());
			break;
			
		case IF:
		case WHILE:
		case IF_ELSE:
			desc.append(this.condition.toString());
			
			for(Statement s : this.getStatements()) {
				desc.append(", ").append(s.toString());
			}
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		return String.format("(%s, \"%s\")", this.getType().toString(), desc.toString());
	}
}
