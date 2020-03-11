<?php include 'questions.php';?>
<?php
if (isset($_SESSION["get1"]))
{
echo '
<h1 class="Welcome">Welcome to the amazing quiz!!</h1>
<h2 class="part">Part 1: The Norm</h2>

<form method="post" action="';
echo htmlspecialchars($_SERVER["PHP_SELF"]);
echo '">';

if (!isset($_SESSION["q11"])){
	echo '<div id="question">
<span>1. ' . $qu11 . '</span><br>
<span><input type="radio" name="q11" value="' . $qa11_1 . '">' . $qa11_1 . '</span>
<span><input type="radio" name="q11" value="' . $qa11_2 . '">' . $qa11_2 . '</span>
<span><input type="radio" name="q11" value="' . $qa11_3 . '">' . $qa11_3 . '</span>
<span><input type="radio" name="q11" value="' . $qa11_4 . '">' . $qa11_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q12"]))
{
echo '<div id="question">
<span>2. ' . $qu12 . '</span><br>
<span><input type="radio" name="q12" value="' . $qa12_1 . '">' . $qa12_1 . '</span>
<span><input type="radio" name="q12" value="' . $qa12_2 . '">' . $qa12_2 . '</span>
<span><input type="radio" name="q12" value="' . $qa12_3 . '">' . $qa12_3 . '</span>
<span><input type="radio" name="q12" value="' . $qa12_4 . '">' . $qa12_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q13"]))
{
echo '<div id="question">
<span>3. ' . $qu13 . '</span><br>
<span><input type="radio" name="q13" value="' . $qa13_1 . '">' . $qa13_1 . '</span>
<span><input type="radio" name="q13" value="' . $qa13_2 . '">' . $qa13_2 . '</span>
<span><input type="radio" name="q13" value="' . $qa13_3 . '">' . $qa13_3 . '</span>
<span><input type="radio" name="q13" value="' . $qa13_4 . '">' . $qa13_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q14"]))
{
echo '<div id="question">
<span>4. ' . $qu14 . '</span><br>
<span><input type="radio" name="q14" value="' . $qa14_1 . '">' . $qa14_1 . '</span>
<span><input type="radio" name="q14" value="' . $qa14_2 . '">' . $qa14_2 . '</span>
<span><input type="radio" name="q14" value="' . $qa14_3 . '">' . $qa14_3 . '</span>
<span><input type="radio" name="q14" value="' . $qa14_4 . '">' . $qa14_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q15"]))
{
echo '<div id="question">
<span>5. ' . $qu15 . '</span><br>
<span><input type="radio" name="q15" value="' . $qa15_1 . '">' . $qa15_1 . '</span>
<span><input type="radio" name="q15" value="' . $qa15_2 . '">' . $qa15_2 . '</span>
<span><input type="radio" name="q15" value="' . $qa15_3 . '">' . $qa15_3 . '</span>
<span><input type="radio" name="q15" value="' . $qa15_4 . '">' . $qa15_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q16"]))
{
echo '<div id="question">
<span>6. ' . $qu16 . '</span><br>
<span><input type="radio" name="q16" value="' . $qa16_1 . '">' . $qa16_1 . '</span>
<span><input type="radio" name="q16" value="' . $qa16_2 . '">' . $qa16_2 . '</span>
<span><input type="radio" name="q16" value="' . $qa16_3 . '">' . $qa16_3 . '</span>
<span><input type="radio" name="q16" value="' . $qa16_4 . '">' . $qa16_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q17"]))
{
echo '<div id="question">
<span>7. ' . $qu17 . '</span><br>
<span><input type="radio" name="q17" value="' . $qa17_1 . '">' . $qa17_1 . '</span>
<span><input type="radio" name="q17" value="' . $qa17_2 . '">' . $qa17_2 . '</span>
<span><input type="radio" name="q17" value="' . $qa17_3 . '">' . $qa17_3 . '</span>
<span><input type="radio" name="q17" value="' . $qa17_4 . '">' . $qa17_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q18"]))
{
echo '<div id="question">
<span>8. ' . $qu18 . '</span><br>
<span><input type="radio" name="q18" value="' . $qa18_1 . '">' . $qa18_1 . '</span>
<span><input type="radio" name="q18" value="' . $qa18_2 . '">' . $qa18_2 . '</span>
<span><input type="radio" name="q18" value="' . $qa18_3 . '">' . $qa18_3 . '</span>
<span><input type="radio" name="q18" value="' . $qa18_4 . '">' . $qa18_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q19"]))
{
echo '<div id="question">
<span>9. ' . $qu19 . '</span><br>
<span><input type="radio" name="q19" value="' . $qa19_1 . '">' . $qa19_1 . '</span>
<span><input type="radio" name="q19" value="' . $qa19_2 . '">' . $qa19_2 . '</span>
<span><input type="radio" name="q19" value="' . $qa19_3 . '">' . $qa19_3 . '</span>
<span><input type="radio" name="q19" value="' . $qa19_4 . '">' . $qa19_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q110"]))
{
echo '<div id="question">
<span>10. ' . $qu110 . '</span><br>
<span><input type="radio" name="q110" value="' . $qa110_1 . '">' . $qa110_1 . '</span>
<span><input type="radio" name="q110" value="' . $qa110_2 . '">' . $qa110_2 . '</span>
<span><input type="radio" name="q110" value="' . $qa110_3 . '">' . $qa110_3 . '</span>
<span><input type="radio" name="q110" value="' . $qa110_4 . '">' . $qa110_4 . '</span>
<br></div>';
}
echo '<br><br>
<input class="send" type="submit" name="submit" value="Submit">';
}
else
{
	include '404.php';
}
?>
