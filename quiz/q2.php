<?php include 'questions.php';?>
<?php
if (isset($_SESSION["get2"]))
{
echo '
<h1 class="Welcome">The Amazing Quiz!!</h1>
<h2 class="part">Part 2: C-stuff</h2>

<form method="post" action="';
echo htmlspecialchars($_SERVER["PHP_SELF"]);
echo '">';

if (!isset($_SESSION["q21"])){
	echo '<div id="question">
<span>1. ' . $qu21 . '</span><br>
<span><input type="radio" name="q21" value="' . $qa21_1 . '">' . $qa21_1 . '</span>
<span><input type="radio" name="q21" value="' . $qa21_2 . '">' . $qa21_2 . '</span>
<span><input type="radio" name="q21" value="' . $qa21_3 . '">' . $qa21_3 . '</span>
<span><input type="radio" name="q21" value="' . $qa21_4 . '">' . $qa21_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q22"]))
{
echo '<div id="question">
<span>2. ' . $qu22 . '</span><br>
<span><input type="radio" name="q22" value="' . $qa22_1 . '">' . $qa22_1 . '</span>
<span><input type="radio" name="q22" value="' . $qa22_2 . '">' . $qa22_2 . '</span>
<span><input type="radio" name="q22" value="' . $qa22_3 . '">' . $qa22_3 . '</span>
<span><input type="radio" name="q22" value="' . $qa22_4 . '">' . $qa22_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q23"]))
{
echo '<div id="question">
<span>3. ' . $qu23 . '</span><br>
<span><input type="radio" name="q23" value="' . $qa23_1 . '">' . $qa23_1 . '</span>
<span><input type="radio" name="q23" value="' . $qa23_2 . '">' . $qa23_2 . '</span>
<span><input type="radio" name="q23" value="' . $qa23_3 . '">' . $qa23_3 . '</span>
<span><input type="radio" name="q23" value="' . $qa23_4 . '">' . $qa23_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q24"]))
{
echo '<div id="question">
<span>4. ' . $qu24 . '</span><br>
<span><input type="radio" name="q24" value="' . $qa24_1 . '">' . $qa24_1 . '</span>
<span><input type="radio" name="q24" value="' . $qa24_2 . '">' . $qa24_2 . '</span>
<span><input type="radio" name="q24" value="' . $qa24_3 . '">' . $qa24_3 . '</span>
<span><input type="radio" name="q24" value="' . $qa24_4 . '">' . $qa24_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q25"]))
{
echo '<div id="question">
<span>5. ' . $qu25  . '</span><br>
<span><input type="radio" name="q25" value="' . $qa25_1 . '">' . $qa25_1 . '</span>
<span><input type="radio" name="q25" value="' . $qa25_2 . '">' . $qa25_2 . '</span>
<span><input type="radio" name="q25" value="' . $qa25_3 . '">' . $qa25_3 . '</span>
<span><input type="radio" name="q25" value="' . $qa25_4 . '">' . $qa25_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q26"]))
{
echo '<div id="question">
<span>6. ' . $qu26 . '</span><br>
<span><input type="radio" name="q26" value="' . $qa26_1 . '">' . $qa26_1 . '</span>
<span><input type="radio" name="q26" value="' . $qa26_2 . '">' . $qa26_2 . '</span>
<span><input type="radio" name="q26" value="' . $qa26_3 . '">' . $qa26_3 . '</span>
<span><input type="radio" name="q26" value="' . $qa26_4 . '">' . $qa26_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q27"]))
{
echo '<div id="question">
<span>7. ' . $qu27 . '</span><br>
<span><input type="radio" name="q27" value="' . $qa27_1 . '">' . $qa27_1 . '</span>
<span><input type="radio" name="q27" value="' . $qa27_2 . '">' . $qa27_2 . '</span>
<span><input type="radio" name="q27" value="' . $qa27_3 . '">' . $qa27_3 . '</span>
<span><input type="radio" name="q27" value="' . $qa27_4 . '">' . $qa27_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q28"]))
{
echo '<div id="question">
<span>8. ' . $qu28 . '</span><br>
<span><input type="radio" name="q28" value="' . $qa28_1 . '">' . $qa28_1 . '</span>
<span><input type="radio" name="q28" value="' . $qa28_2 . '">' . $qa28_2 . '</span>
<span><input type="radio" name="q28" value="' . $qa28_3 . '">' . $qa28_3 . '</span>
<span><input type="radio" name="q28" value="' . $qa28_4 . '">' . $qa28_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q29"]))
{
echo '<div id="question">
<span>9. ' . $qu29 . '</span><br>
<span><input type="radio" name="q29" value="' . $qa29_1 . '">' . $qa29_1 . '</span>
<span><input type="radio" name="q29" value="' . $qa29_2 . '">' . $qa29_2 . '</span>
<span><input type="radio" name="q29" value="' . $qa29_3 . '">' . $qa29_3 . '</span>
<span><input type="radio" name="q29" value="' . $qa29_4 . '">' . $qa29_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q210"]))
{
echo '<div id="question">
<span>10. ' . $qu210 . '</span><br>
<span><input type="radio" name="q210" value="' . $qa210_1 . '">' . $qa210_1 . '</span>
<span><input type="radio" name="q210" value="' . $qa210_2 . '">' . $qa210_2 . '</span>
<span><input type="radio" name="q210" value="' . $qa210_3 . '">' . $qa210_3 . '</span>
<span><input type="radio" name="q210" value="' . $qa210_4 . '">' . $qa210_4 . '</span>
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
