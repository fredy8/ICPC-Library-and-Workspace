def docs():
	print('docs')
	
def include():
	print('include')


import re
import os
import subprocess
from tempfile import TemporaryFile

def compile(workspaceDir):
	return not subprocess.call(['g++', '-iquote', workspaceDir + 'lib/', '-DDEBUG', '-o', 'problem', workspaceDir + 'problem.cpp'])


def create_input(workspaceDir):
	with open(workspaceDir + 'problem.cpp') as sourceFile:
		match = re.match(r'/\*\s*\n(.*)\n\*/', sourceFile.read())
		if match:
			inputFile = TemporaryFile('w+')
			inputFile.write(match.group(1))
			inputFile.seek(0)
			return inputFile

	inputFilePath = workspaceDir + 'input.txt'
	if os.path.isfile(inputFilePath):
		return open(inputFilePath)

	return None


def run(workspaceDir):
	if not compile(workspaceDir):
		return

	with create_input(workspaceDir) as input:
		subprocess.call(['./problem'], stdin=input)

	os.remove('./problem')

commands = {
	"run": run,
	"include": include,
	"docs": docs,
}

print('[Placeholder for description]')

exit = False
while(not exit):
	command, *args = input('> ').split(' ')
	if command == 'exit':
		exit = True
	elif command in commands.keys():
		commands[command](*args)
	else:
		print('Command not found')