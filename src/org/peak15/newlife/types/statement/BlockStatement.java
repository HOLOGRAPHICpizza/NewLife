package org.peak15.newlife.types.statement;

import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;


/**
 * List of zero or more statements.
 */
public final class BlockStatement implements Statement, Iterable<Statement> {
	
	private final List<Statement> list;
	
	private static final BlockStatement EMPTY_BLOCK = new BlockStatement.Builder().build();
	
	public static BlockStatement emptyBlock() {
		return EMPTY_BLOCK;
	}
	
	/**
	 * @param statements a list of zero or more statements.
	 */
	public BlockStatement(List<? extends Statement> statements) {
		if(statements == null) {
			throw new NullPointerException("No parameters may be null.");
		}
		/*else if(statements.size() < 1) {
			throw new IllegalArgumentException("A block must contain at least one statement.");
		}*/
		
		this.list = new LinkedList<>(statements);
	}
	
	public final static class Builder {
		
		private List<Statement> list = new LinkedList<>();
		
		public Builder() {}
		
		public Builder(Statement first) {
			this.append(first);
		}
		
		public Builder append(Statement statement) {
			if(statement == null) {
				throw new NullPointerException("Blocks may not contain null statements.");
			}
			
			list.add(statement);
			return this;
		}
		
		public BlockStatement build() {
			return new BlockStatement(list);
		}
	}
	
	/**
	 * @return an immutable view of the backing list for this block.
	 */
	public List<Statement> statementList() {
		return Collections.unmodifiableList(list);
	}
	
	public int size() {
		return list.size();
	}
	
	/**
	 * @param index the (zero indexed) index of the desired element
	 * @return the element with the given index
	 */
	public Statement get(int index) {
		return this.statementList().get(index);
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof BlockStatement)) {
			return false;
		}
		
		BlockStatement s = (BlockStatement) obj;
		
		return s.statementList().equals(this.statementList());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.statementList().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("<block: %d statements>", this.size());
	}

	@Override
	public Iterator<Statement> iterator() {
		return this.statementList().iterator();
	}
}
