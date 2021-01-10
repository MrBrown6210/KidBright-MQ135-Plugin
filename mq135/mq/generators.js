Blockly.JavaScript['mq.random-text'] = function (block) {
  return [`DEV_IO.mq().random()`, Blockly.JavaScript.ORDER_ATOMIC]
}

Blockly.JavaScript['mq.basic_string'] = function (block) {
  return [`DEV_IO.mq().random()`, Blockly.JavaScript.ORDER_ATOMIC]
}

Blockly.JavaScript['mq.recieved'] = function(block) {
	var statement = Blockly.JavaScript.statementToCode(block, 'DO');
	return 'DEV_IO.mq().callback([](){'+statement+'});\n';
};

Blockly.JavaScript['mq.didEnter'] = function(block) {
	var statement = Blockly.JavaScript.statementToCode(block, 'DO');
	return 'DEV_IO.mq().didEnter([](){'+statement+'});\n';
};

Blockly.JavaScript['mq.data'] = function (block) {
  return [`DEV_IO.mq().distance()`];
};