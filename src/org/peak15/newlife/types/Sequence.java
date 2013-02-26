package org.peak15.newlife.types;

import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public final class Sequence<E> implements Iterable<E> {
	
	private final List<E> list;
	
	private Sequence(Builder<E> b) {
		this.list = b.list;
	}
	
	
	public static <E> Sequence<E> emptySequence() {
		return new Builder<E>().build();
	}
	
	public List<E> asList() {
		return Collections.unmodifiableList(list);
	}
	
	public int size() {
		return list.size();
	}
	
	/**
	 * @param index the (zero indexed) index of the desired element
	 * @return the element with the given index
	 */
	public E get(int index) {
		return this.list.get(index);
	}
	
	@Override
	public Iterator<E> iterator() {
		return this.asList().iterator();
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof Sequence<?>)) {
			return false;
		}
		
		Sequence<?> s = (Sequence<?>) obj;
		
		return s.asList().equals(this.asList());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.asList().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("<sequence: %d elements>", this.size());
	}
	
	public final static class Builder<E> {
		
		private final List<E> list = new LinkedList<>();
		
		public Builder() {}
		
		public Builder(E first) {
			this.append(first);
		}
		
		public Builder(List<? extends E> list) {
			this.append(list);
		}
		
		public Builder(Sequence<? extends E> seq) {
			this.append(seq.asList());
		}
		
		public Builder<E> append(E e) {
			if(e == null) {
				throw new NullPointerException("Sequence elements may not be null.");
			}
			this.list.add(e);
			return this;
		}
		
		public Builder<E> append(List<? extends E> list) {
			if(list == null) {
				throw new NullPointerException("Sequence elements may not be null.");
			}
			this.list.addAll(list);
			return this;
		}
		
		public Builder<E> append(Sequence<? extends E> seq) {
			if(seq == null) {
				throw new NullPointerException("Sequence elements may not be null.");
			}
			this.list.addAll(seq.asList());
			return this;
		}
		
		public Sequence<E> build() {
			return new Sequence<E>(this);
		}
	}
}
