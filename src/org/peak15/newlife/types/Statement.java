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
}
