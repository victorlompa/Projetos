## Projeto Final

### Genius
Genius ou simon (como é conhecido em inglês) é um jogo que consiste em memorizar uma sequência apresentada por um brinquedo em forma de disco com botões coloridos que acendem e tocam sons. Após apresentar uma sequência aleatória, o brinquedo aguarda o jogador apertar os botões na mesma ordem. Caso ela seja incorreta, o genius dispara uma sequência de luzes e sons indicando que o jogador perdeu e, caso seja correta, o genius apresenta a mesma sequência porém desta vez com um botão aleatório a mais para ser memorizado. O jogo possui um número finito de repetições para que o jogador consiga vencer, resultando em uma sequência de luzes e sons que indicam a vitória.

### Requisitos e Informações
O jogo foi desenvolvido para a unidade curricular de microprocessadores, lecionada pelo professor Hugo Marcondes do Instituto Federal de Santa Catarina (IFSC) e utilizamos o simulador MARS e a linguagem MIPS. O jogo deveria ter a dificuldade configurável por dois parâmetros: o número de repetições para se vencer o jogo e a velocidade com que as repetições são apresentadas: o tempo de duração da luz e do som. A entrada de dados foi configurada para funcionar com as teclas 7, 9, 1 e 3 do teclado numérico, que correspondem às cores verde, vermelho, amarelo e azul, respectivamente.

### Código
O código foi divido em diversos macros e procedimentos para que se tornasse mais limpo e compreensível. Alguns dados como o tempo de repetição base de cada pulso luminoso em caso de vitória e derrota e as cores de cada pulso foram colocados no início do código para que se tornem mais facilmente editáveis. O código possui também o tratamento de erros em seu final para que, no pior dos casos, encerre o programa e apresente o código do erro que iniciou o processo.


```assembly
# --------------------------------------------- Data
.data
display:    .space 4096

totaly:     .word  32
farright:   .word  31
midright:   .word  16
midleft:    .word  15
farleft:    .word  0

blue_on:    .word  0x000000cf
green_on:   .word  0x0000cf00
red_on:     .word  0x00cf0000
yellow_on:  .word  0x00cfcf00
white_on:   .word  0x00cfcfcf

blue_off:   .word  0x00000040
green_off:  .word  0x00004000
red_off:    .word  0x00400000
yellow_off: .word  0x00404000

switch_case: .word 0x33, 0x37, 0x39, 0x31

bresenham:   .float 0.5
maxsize:     .word  16

.align 2
onetwo:	     .space 8
resp:	     .space 8
sec:	     .space 8
var1:        .space 4

bem_vindo:   .asciiz "Bem vindo ao programa Genius!\n1- Iniciar o jogo.\n2- Encerrar o programa."
selecao:     .asciiz "Digite o número de ativações:"
selecao2:    .asciiz "Digite a duração de ativação (ms):"
invalido:    .asciiz "Valor inválido, tente novamente.\n"
showtot:     .asciiz "Total de níveis: "
show:	     .asciiz "Nível atual:     "
tuto:	     .asciiz "Verde:   7  | Vermelho: 9\nAmarelo: 1  | Azul:     3\n\n"
enter:       .asciiz "Aperte enter para começar."
vitoria:     .asciiz "Parabéns! Você venceu."
derrota:     .asciiz "Você perdeu..."
jump:	     .asciiz "\n"
erro: 	     .asciiz "\nOcorreu um erro inesperado.\nO programa será desligado."

# Start flags
.macro geniusCreate (%nome, %start, %actualLevel, %partLevel, %maxLevel, %bufferSpace)
.data
.align 2
%nome:
	.word  %start
	.word  %actualLevel
	.word  %partLevel
	.word  %maxLevel
	.space %bufferSpace
.end_macro

# Create ringbuffer
.macro ringbuffer (%nome, %size, %rd, %wr)
.data
.align 2
%nome:
	.word  %size
	.word  %rd
	.word  %wr
	.space 64
.end_macro

# Sound
.macro midia(%pitch, %duration, %instrument, %volume)
	li $a0, %pitch
	li $a1, %duration
	li $a2, %instrument
	li $a3, %volume
	li $v0, 31
	syscall
.end_macro

# Sound 2 ( Using lw in a .data )
.macro midiacd(%pitch, %duration, %instrument, %volume)
	li $a0, %pitch
	lw $a1, %duration
	li $a2, %instrument
	li $a3, %volume
	li $v0, 31
	syscall
.end_macro

# Pause
.macro sleep(%miliseconds)
.text
	li $a0, %miliseconds
	li $v0, 32
	syscall
.end_macro

# Pause 2 ( Using lw in a .data )
.macro sleepcd(%miliseconds)
.text
	lw $a0, %miliseconds
	li $v0, 32
	syscall
.end_macro

# Create a seed
.macro seed
	li $v0, 30	
	syscall
	move $a1, $a0
	li $v0, 40
	li $a0, 0
	syscall
.end_macro

# Get random number
.macro random
.text	
	li $v0, 42
	li $a0, 0
	li $a1, 4
	syscall
	move $v0, $a0
.end_macro

# Draw rectangle in Bitmap Display
.macro drawRectangle (%x0, %y0, %x1, %y1, %color)
	lw $t0, %color
	sw $t0, 16($sp)
	lw $a0, %x0
	lw $a1, %y0
	lw $a2, %x1
	lw $a3, %y1
	jal drawRectangle
.end_macro

# Draw a pixel in Bitmap Display
.macro setPixel (%x0, %y0, %color)
	li $a0, %x0
	li $a1, %y0
	li $a2, %color
	jal setPixel
.end_macro

# Draw a line in Bitmap Display
.macro drawLine (%x0, %y0, %x1, %y1, %color)
	lw $t0, %color
	sw $t0, 16($sp)
	li $a0, %x0
	li $a1, %y0
	li $a2, %x1
	li $a3, %y1
	jal drawLine
.end_macro

# Turn all colors On
.macro drawGenius_On
.text	
	drawRectangle(farleft, farleft, midleft, midleft, green_on)
	drawRectangle(midright, farleft, farright, midleft, red_on)
	drawRectangle(farleft, midright, midleft, farright, yellow_on)
	drawRectangle(midright, midright, farright, farright, blue_on)
.end_macro

# Turn all colors off
.macro drawGenius_Off
.text	
	drawRectangle(farleft, farleft, midleft, midleft, green_off)
	drawRectangle(midright, farleft, farright, midleft, red_off)
	drawRectangle(farleft, midright, midleft, farright, yellow_off)
	drawRectangle(midright, midright, farright, farright, blue_off)
.end_macro

# Print a string MMIO simulator
.macro print_string (%string)
	la $a0, %string
	jal print_string
.end_macro

ringbuffer   (rb, 0, 0, 0)
geniusCreate (gen, 1, 1, 0, 5, 4000)

# --------------------------------------------- Text
.text
# Init
init:
	la $sp, 0x7fffeffc
	jal main
	li $v0, 10
	syscall

# Main	
main:
	addi $sp, $sp, -40
	sw $s1, 32($sp)
	sw $s0, 28($sp)
	sw $v0, 24($sp)
	sw $ra, 20($sp)
	drawGenius_Off
	
# Menu de Seleção
menu_get_start:
	print_string(bem_vindo)
	la   $a0, onetwo
	jal  getLine
	la   $a0, onetwo
	jal  convert
	blt  $v0, 1, menu_invalid_start
	bgt  $v0, 2, menu_invalid_start
	beq  $v0, 1, menu_part1_start
	la   $t0, genius_end
	jr   $t0	
menu_invalid_start:
	la  $t0, onetwo
	sw  $zero, 0($t0)
	sw  $zero, 4($t0)
	jal reset_display
	print_string(invalido)
	b menu_get_start

menu_part1_start:
	jal reset_display
menu_part1:
	print_string(selecao)
	la  $a0, resp
	jal getLine
	la  $a0, resp
	jal convert
	beq $v0, $zero, menu_part1_invalid
	la  $t0, gen
	sw  $v0, 12($t0)
	b   menu_part2_start
menu_part1_invalid:
	jal reset_display
	print_string(invalido)
	la  $t0, resp
	sw  $zero, 0($t0)
	sw  $zero, 4($t0)
	b menu_part1
	
menu_part2_start:
	jal reset_display
menu_part2:
	print_string(selecao2)
	la  $a0, sec
	jal getLine
	la  $a0, sec
	jal convert
	beq $v0, $zero, menu_part2_invalid
	la  $t0, sec
	sw  $v0, 0($t0)
	b   menu_end
menu_part2_invalid:
	jal reset_display
	print_string(invalido)
	la  $t0, sec
	sw  $zero, 0($t0)
	sw  $zero, 4($t0)
	b menu_part2

menu_end:
	jal reset_display
	print_string(showtot)
	print_string(resp)
	print_string(tuto)
	print_string(enter)
	jal wait

first_start:
	jal reset_display
	seed
	midia(61, 500, 98, 50)
	drawGenius_On
	sleep(300)
	drawGenius_Off
	sleep(100)
	midia(61, 500, 98, 50)
	drawGenius_On
	sleep(300)
	drawGenius_Off
	
start_level:
	jal  disable_kbint
	jal  reset_display
	la   $t0, var1
	la   $t2, gen
	lw   $t1, 4($t2)
	addi $t1, $t1, 48
	sw   $t1, 0($t0)
	print_string(showtot)
	print_string(resp)
	print_string(show)
	print_string(var1)
	print_string(jump)
	print_string(jump)
	print_string(tuto)
	
# Check if all colors have been generated
check_level:
	la $t0, gen
	lw $t1, 4($t0) # Actual Level 1-5
	lw $t2, 8($t0) # Genius Buffer size 0-5
	beq $t2, $t1, show_colors
		
# Select random color to show
new_random_color:
	random
	la  $t0, switch_case
	sll $t1, $v0, 2
	add $t0, $t0, $t1
	lw  $s0, 0($t0)
	jal geniusGetAddr
	sw $s0, 0($v0)	
	j check_level
	
# Show all colors
show_colors:
	la $s0, gen
	sw $0, 8($s0)
show_colors_loop:
	jal geniusGetAddr
	lw  $s0, 0($v0)
	sleep(500)
	bge $s0, 0x39, red
	bge $s0, 0x37, green
	bge $s0, 0x33, blue
	bge $s0, 0x31, yellow
	b wait_answer
	
yellow:
	midiacd(62, sec, 98, 50)
	drawRectangle(farleft, midright, midleft, farright, yellow_on)
	sleepcd(sec)
	drawRectangle(farleft, midright, midleft, farright, yellow_off)
	b show_colors_loop	
blue:
	midiacd(64, sec, 98, 50)
	drawRectangle(midright, midright, farright, farright, blue_on)
	sleepcd(sec)
	drawRectangle(midright, midright, farright, farright, blue_off)
	b show_colors_loop
green:
	midiacd(67, sec, 98, 50)
	drawRectangle(farleft, farleft, midleft, midleft, green_on)
	sleepcd(sec)
	drawRectangle(farleft, farleft, midleft, midleft, green_off)
	b show_colors_loop
red:
	midiacd(69, sec, 98, 50)
	drawRectangle(midright, farleft, farright, midleft, red_on)
	sleepcd(sec)
	drawRectangle(midright, farleft, farright, midleft, red_off)
	b show_colors_loop
	
# Wait for answer
wait_answer:  
	la  $s0, gen
	sw  $0, 8($s0)
	jal enable_kbint
	la  $a0, rb
wait_answer_loop:
	jal  rbuf_empty
	bne  $v0, $0, wait_answer_loop
	
	# Check the answer
	jal  rbuf_read
	la   $s0, gen
	move $s1, $v0
	lw   $t0, 8($s0)
	addi $t1, $t0, 1
	sw   $t1, 8($s0)
	sll  $t0, $t0, 2
	add  $t0, $s0, $t0
	addi $t0, $t0, 16
	lw   $s2, 0($t0)
	bne  $s1, $s2, lose
	
	# Check if there is next answer
	lw   $t0, 4($s0)
	lw   $t1, 8($s0)
	bgt  $t0, $t1, wait_answer_loop
	
	# Upgrade Level Difficulty
	addi $t0, $t0, 1
	lw   $t1, 12($s0)
	bgt  $t0, $t1, win
	sw   $t0, 4($s0)
	j start_level

win:
	jal reset_display
	print_string(vitoria)
	drawGenius_On
	midia(61, 200, 98, 50)
	sleep(200)
	midia(61, 200, 98, 50)
	sleep(200)
	midia(61, 500, 98, 50)
	sleep(500)
	drawGenius_Off
	b genius_end

lose:
	jal reset_display
	print_string(derrota)
	drawGenius_On
	midia(51, 1000, 20, 50)
	sleep(1000)
	midia(50, 800, 20, 50)
	sleep(800)
	midia(49, 900, 20, 50)
	sleep(900)
	midia(43, 2100, 20, 50)
	sleep(2100)
	drawGenius_Off
		
genius_end:
	lw   $ra, 20($sp)
	lw   $v0, 24($sp)
	lw   $s0, 28($sp)
	lw   $s1, 32($sp)
	addi $sp, $sp, 40
	jr   $ra
	
# --------------------------------------------- Genius
# Void geniusGetAdress (char)
geniusGetAddr:
	la   $t0, gen		
	lw   $t1, 8($t0)	
	addi $t2, $t1, 1	
	sw   $t2, 8($t0)
	
	addi $t0, $t0, 16
	sll  $t1, $t1, 2	
	add  $v0, $t0, $t1		
	jr   $ra
	
# --------------------------------------------- Bitmap Display
# Void setPixel (int x, int y, int color)
setPixel:
	la  $t0, display	
	sll $t1, $a0, 2		
	lw  $t2, totaly		
	mul $t2, $t2, $a1	
	sll $t2, $t2, 2 	
	add $t0, $t0, $t1
	add $t0, $t0, $t2
	sw  $a2, 0($t0)
	jr  $ra
	
# Void drawLine (int x0, int y0, int x1, int y1, int color)
drawLine:
	addi 	$sp, $sp, -8
	sw   	$ra, 4 ($sp)
	sub     $s0, $a2, $a0			
	sub     $s1, $a3, $a1			
	abs     $s2, $s0			
	abs	$s3, $s1			
	bge	$s2, $s3, drawLine_check_x				
	bge	$a3, $a1, drawLine_save_args	
	b 	drawLine_invert
drawLine_check_x:				
	bge  	$a2, $a0, drawLine_save_args	
drawLine_invert:				
	move 	$t0, $a0
	move 	$a0, $a2	
	move 	$a2, $t0	
	move 	$t0, $a1
	move 	$a1, $a3	
	move 	$a3, $t0
	sub 	$s0, $a2, $a0
	sub	$s1, $a3, $a1
drawLine_save_args:
	sw   	$a0, 8($sp)		
	sw   	$a1, 12($sp)			
	sw   	$a2, 16($sp)			 
	sw   	$a3, 20($sp)			
	beq 	$s0, $zero, for_drawLine_vertical
	beq     $s1, $zero, for_drawLine_horizontal
	mtc1    $s0, $f0
	mtc1    $s1, $f1
        cvt.s.w $f0, $f0 
        cvt.s.w $f1, $f1
        div.s   $f0, $f1, $f0		
        abs.s   $f0, $f0			
	li      $t0, 0
	mtc1    $t0, $f1
        cvt.s.w $f1, $f1
	l.s     $f2, bresenham			
	li      $t0, 1				
	mtc1    $t0, $f3
	cvt.s.w $f3, $f3
	bgt $s0, $zero, drawLine_positive_dx
	li  $s0, -1
	b   drawLine_check_dx_end
	drawLine_positive_dx:
	li  $s0, 1
drawLine_check_dx_end:
	bgt $s1, $zero, drawLine_positive_dy
	li  $s1, -1
	b   drawLine_check_dy_end
	drawLine_positive_dy:
	li  $s1, 1
drawLine_check_dy_end:
	bgt     $s3, $s2, for_drawLine_dy
for_drawLine_dx:
	bgt    $a0, $a2, for_drawLine_end	
	lw     $a2, 24($sp)			
	jal    setPixel				
	lw     $a2, 16($sp)		
	add.s  $f1, $f1, $f0		
        c.lt.s $f1, $f2 			
        bc1t   drawLine_error_end_dx		
		add  $a1, $a1, $s1		
		sub.s $f1, $f1, $f3		
	drawLine_error_end_dx:
		addi  $a0, $a0, 1		
		b     for_drawLine_dx
for_drawLine_dy:
	bgt    $a1, $a3, for_drawLine_end	
	lw     $a2, 24($sp)			
	jal    setPixel				
	lw     $a2, 16($sp)			
	add.s  $f1, $f1, $f0			
	c.lt.s $f1, $f2				
	bc1t   drawLine_error_end_dy		
		add   $a0, $a0, $s0		
		sub.s $f1, $f1, $f3		
	drawLine_error_end_dy:
		addi $a1, $a1, 1		
		b    for_drawLine_dx
for_drawLine_horizontal:		
	bgt  $a0, $a2, for_drawLine_end
	lw   $a2, 24($sp)
	jal  setPixel
	lw   $a2, 16($sp)
	addi $a0, $a0, 1
	b    for_drawLine_horizontal
for_drawLine_vertical:
	bgt  $a1, $a3, for_drawLine_end
	lw   $a2, 24($sp)
	jal  setPixel
	lw   $a2, 16($sp)
	addi $a1, $a1, 1
	b    for_drawLine_vertical				
for_drawLine_end:
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	jr   $ra
	
# Void drawRectangle (int x0, int y0, int x1, int y1, int color)
drawRectangle:
	addi $sp, $sp, -8
	sw   $ra, 4($sp)
	
	bge  $a2, $a0, drawRectangle_align
	move $t0, $a0
	move $a0, $a2	
	move $a2, $t0
drawRectangle_align:
	bge  $a3, $a1, drawRectangle_save_args	
	move $t0, $a1
	move $a1, $a3	
	move $a3, $t0
	
drawRectangle_save_args:
	sw  $a0, 8($sp)
	sw  $a1, 12($sp)
	sw  $a2, 16($sp)
	sw  $a3, 20($sp)
	
for_drawRectangle_y:
	bgt $a1, $a3, for_drawRectangle_y_end
	
	for_drawRectangle_x:
		bgt  $a0, $a2, for_drawRectangle_x_end
		lw   $a2, 24($sp)
		jal  setPixel
		lw   $a2, 16($sp)
		addi $a0, $a0, 1
		b    for_drawRectangle_x
		
	for_drawRectangle_x_end:
	lw   $a0, 8($sp)
	addi $a1, $a1, 1
	b    for_drawRectangle_y
	
for_drawRectangle_y_end:
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	jr   $ra

# --------------------------------------------- Keyboard and Display
# int Convert_Line (char *string)
convert:
	li $v0, 0
	li $t0, 1
	li $t2, 1
	li $t3, 0
	
check_len_loop:
	lb   $t1, 0($a0)
	beq  $t1, 10, check_len_loop_end
	addi $t3, $t3, 1
	addi $a0, $a0, 1
	b check_len_loop
check_len_loop_end:
	sub  $a0, $a0, $t3
	
convert_parameter_calc:
	beq  $t2, $t3, convert_loop
	mul  $t0, $t0, 10
	addi $t2, $t2, 1
	b convert_parameter_calc
convert_loop:
	lb  $t1, 0($a0)
	beq $t1, 10, convert_end
	blt $t1, 48, convert_invalid
	bgt $t1, 57, convert_invalid
	sub $t1, $t1, 48
	bne $t1, $zero, convert_continue
convert_not_zero:
		beq  $v0, $zero, convert_left_zero
		addi $t1, $t1, 1
		b convert_continue
convert_left_zero:
		addi $a0, $a0, 1
		b convert_loop
convert_continue:
	mul  $t1, $t1, $t0
	add  $v0, $v0, $t1
	div  $t0, $t0, 10
	addi $a0, $a0, 1
	b convert_loop
convert_invalid:
	li $v0, 0
convert_end:
	jr $ra

# void getLine (char *string)
getLine:
	lui  $t0, 0xffff	
getLine_loop:
	lw     $t1, 0($t0)		
	andi   $t1, $t1, 0x1		
	beq    $t1, $zero, getLine_loop
	
	lb    $t2, 4($t0)	
	sb    $t2, 0($a0)	
	beq   $t2, 10, getLine_end	
	addu  $a0, $a0, 1
	b getLine_loop
getLine_end:
	jr    $ra

# void print_string (char *string)
print_string:
	la $t0, 0xffff0008
	
print_string_loop:
	lw   $t1, 0($t0)
	andi $t1, $t1, 1
	beq  $t1, $zero, print_string_loop
	
	lb  $t2, 0($a0)
	beq $t2, $zero, print_string_loop_end
	sb  $t2, 4($t0)
	addiu $a0, $a0, 1
	b print_string_loop
	
print_string_loop_end:
	jr $ra
	
# Reset Display
reset_display:
	la $t0, 0xffff0008

reset_display_loop:
	lw   $t1, 0($t0)
	andi $t1, $t1, 1
	beq  $t1, $zero, reset_display_loop
	li   $t2, 12
	sb   $t2, 4($t0)
	jr   $ra
	
# Wait Enter
wait:
	lui  $t0, 0xffff	
wait_loop:
	lw     $t1, 0($t0)		
	andi   $t1, $t1, 0x1		
	beq    $t1, $zero, wait_loop
	
	lb    $t2, 4($t0)	
	beq   $t2, 10, wait_end	
	b wait_loop
wait_end:
	jr    $ra

# Enable Keyboard Interrupts
enable_kbint:
	addi $sp, $sp, -8
	sw   $ra, 4($sp)
	jal  disable_int
	lui  $t0, 0xffff
	lw   $t1, 0($t0)
	ori  $t1, $t1, 0x0002
	sw   $t1, 0($t0)	
	mfc0 $t0, $12
	ori  $t0, $t0, 0x0100
	mtc0 $t0, $12		
	jal  enable_int
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	jr   $ra
	
# Disable Keyboard Interrupts
disable_kbint:
	addi $sp, $sp, -8
	sw   $ra, 4($sp)
	jal  disable_int
	lui  $t0, 0xffff
	lw   $t1, 0($t0)
	andi $t1, $t1, 0xfffd
	sw   $t1, 0($t0)
	jal  enable_int
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	jr   $ra
	
# Enable Interrupts
enable_int:
	mfc0 $t0, $12
	ori  $t0, $t0, 0x0001
	mtc0 $t0, $t2
	jr   $ra
	
# Disable Interrupts
disable_int:
	mfc0 $t0, $12
	andi $t0, $t0, 0xfffffffe
	mtc0 $t0, $t2
	jr   $ra

# char read(t_ringbuffer *rbuf)
rbuf_read:
	addi $sp, $sp, -8
	sw   $ra, 0($sp)
	jal  disable_int
	jal  rbuf_empty		
	li   $t0, 0		
	beq  $v0, 1, rbuf_read_end
		lw   $t1, 0($a0)	
		subi $t1, $t1, 1	
		sw   $t1, 0($a0)	
		lw   $t1, 4($a0)		
		sll  $t2, $t1, 2		
		add  $t2, $t2, $a0		
		addi $t2, $t2, 12	
		lw   $t0, 0($t2)		
		addi $t1, $t1, 1		
		lw   $t2, maxsize
		rem  $t1, $t1, $t2		
		sw   $t1, 4($a0)		
rbuf_read_end:
	move $v0, $t0
	jal  enable_int
	lw   $ra, 0($sp)
	addi $sp, $sp 8
	jr   $ra	

# bool write(t_ringbuffer *rbuf, char byte)
rbuf_write:
	addi $sp, $sp -8
	sw   $ra, 4($sp)
	jal  disable_int
	jal  rbuf_full		
	beq  $v0, 1, rbuf_write_full
		lw   $t0, 0($a0)		
		addi $t0, $t0, 1		
		sw   $t0, 0($a0)		
		lw   $t0, 8($a0)		
		sll  $t1, $t0, 2		
		add  $t1, $t1, $a0		
		addi $t1, $t1, 12		
		sw   $a1, 0($t1)		
		addi $t0, $t0, 1		
		lw   $t1, maxsize
		rem  $t2, $t0, $t1		
		sw   $t2, 8($a0)	
		li   $v0, 1
		j rbuf_write_end
rbuf_write_full:
	li   $v0, 0
rbuf_write_end:
	jal  enable_int
	
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	jr   $ra

# boolf rbuf_empty (t_ringbuffer *rbuf)
rbuf_empty:
	lw  $t0, 0($a0)
	bne $t0, $0, not_empty
	li  $v0, 1
	jr  $ra
not_empty:
	li  $v0, 0
	jr  $ra

# bool rbuf_full (t_ringbuffer *rbuf)
rbuf_full:
	lw  $t0, 0($a0)
	lw  $t1, maxsize
	bne $t0, $t1, not_full
	li  $v0, 1
	jr  $ra
not_full:
	li  $v0, 0
	jr  $ra

# --------------------------------------------- Kernel	
.ktext 0x80000180
	move $k0, $1
	la   $k1, _regs  
	sw   $k0, 0($k1)
	sw   $2 , 4($k1)
	sw   $3 , 8($k1)  
	sw   $4 , 12($k1) 
	sw   $5 , 16($k1)
	sw   $6 , 20($k1)
	sw   $7 , 24($k1)
	sw   $8 , 28($k1) 
	sw   $9 , 32($k1) 
	sw   $10, 36($k1) 
	sw   $11, 40($k1) 
	sw   $12, 44($k1) 
	sw   $13, 48($k1) 
	sw   $14, 52($k1) 
	sw   $15, 56($k1)
	sw   $16, 60($k1)
	sw   $17, 64($k1)
	sw   $18, 68($k1)
	sw   $19, 72($k1)
	sw   $20, 76($k1)
	sw   $21, 80($k1)
	sw   $22, 84($k1)
	sw   $23, 88($k1)
	sw   $24, 92($k1)
	sw   $25, 96($k1)
	sw   $26, 100($k1)
	sw   $27, 104($k1)
	sw   $28, 108($k1)
	sw   $29, 112($k1)
	sw   $30, 116($k1)
	sw   $31, 120($k1)
	
	mfc0 $a0, $13
	andi $a0, $a0, 0x7c
	bne  $a0, $zero, exc
	
	la   $a0, rb
	lui  $t0, 0xffff
	lw   $t1, 0($t0)
	andi $t1, $t1, 0x1
	beq  $t1, $0,  int_end
	lw   $a1, 4($t0)
	la   $k0, rbuf_write
	jalr $k0
	midia(51, 100, 9, 50)
	j    int_end
	
exc:
	li $v0, 17
	syscall
int_end:
	mtc0 $0, $13			
	lw   $1 , 0($k1)
	lw   $2 , 4($k1)
	lw   $3 , 8($k1)  
	lw   $4 , 12($k1) 
	lw   $5 , 16($k1)
	lw   $6 , 20($k1)
	lw   $7 , 24($k1)
	lw   $8 , 28($k1) 
	lw   $9 , 32($k1) 
	lw   $10, 36($k1) 
	lw   $11, 40($k1) 
	lw   $12, 44($k1) 
	lw   $13, 48($k1) 
	lw   $14, 52($k1) 
	lw   $15, 56($k1)
	lw   $16, 60($k1)
	lw   $17, 64($k1)
	lw   $18, 68($k1)
	lw   $19, 72($k1)
	lw   $20, 76($k1)
	lw   $21, 80($k1)
	lw   $22, 84($k1)
	lw   $23, 88($k1)
	lw   $24, 92($k1)
	lw   $25, 96($k1)
	lw   $26, 100($k1)
	lw   $27, 104($k1)
	lw   $28, 108($k1)
	lw   $29, 112($k1)
	lw   $30, 116($k1)
	lw   $31, 120($k1) 
	eret

# --------------------------------------------- Kdata
.kdata
_regs:    .space 124
```
