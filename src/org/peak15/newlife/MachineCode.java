package org.peak15.newlife;

public enum MachineCode {
	MOVE(0x00),
	TURNLEFT(0x01),
	TURNRIGHT(0x02),
	INFECT(0x03),
	SKIP(0x04),
	HALT(0x05),
	JUMP(0x06),
	JUMP_IF_NOT_NEXT_IS_EMPTY(0x07),
	JUMP_IF_NOT_NEXT_IS_NOT_EMPTY(0x08),
	JUMP_IF_NOT_NEXT_IS_WALL(0x09),
	JUMP_IF_NOT_NEXT_IS_NOT_WALL(0x0A),
	JUMP_IF_NOT_NEXT_IS_FRIEND(0x0B),
	JUMP_IF_NOT_NEXT_IS_NOT_FRIEND(0x0C),
	JUMP_IF_NOT_NEXT_IS_ENEMY(0x0D),
	JUMP_IF_NOT_NEXT_IS_NOT_ENEMY(0x0E),
	JUMP_IF_NOT_RANDOM(0x0F),
	JUMP_IF_NOT_TRUE(0x10);
	
	private final byte value;
	
	private MachineCode(int value) {
		this((byte) value);
	}
	
	private MachineCode(byte value) {
		this.value = value;
	}
	
	public byte value() {
		return value;
	}
}
