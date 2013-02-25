package org.peak15.newlife.types;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import org.peak15.newlife.MachineCode;

public final class CompiledProgram {
	
	private final List<MachineCode> list;
	
	private CompiledProgram(Builder b) {
		this.list = b.list;
	}
	
	public List<MachineCode> asList() {
		return Collections.unmodifiableList(list);
	}
	
	public static final class Builder {
		private final List<MachineCode> list = new LinkedList<>();
		
		public Builder() {}
		
		public Builder(MachineCode first) {
			this.append(first);
		}
		
		public Builder(List<MachineCode> list) {
			this.appendAll(list);
		}
		
		public Builder append(MachineCode c) {
			if(c == null) {
				throw new NullPointerException("The machine code may not be null.");
			}
			this.list.add(c);
			return this;
		}
		
		public Builder appendAll(List<MachineCode> list) {
			if(list == null) {
				throw new NullPointerException("The list may not be null.");
			}
			this.list.addAll(list);
			return this;
		}
		
		public CompiledProgram build() {
			return new CompiledProgram(this);
		}
	}
}
