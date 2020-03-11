<?php include 'questions.php'; ?>
<?php
if (isset($_SESSION["get3"]))
{
	if (!isset($_SESSION["end"]))
		$_SESSION["end"] = time();
echo '
<h1 class="Welcome">The Amazing Quiz!!</h1>
<h2 class="part">Part 3: The You</h2>

<form method="post" action="';
echo htmlspecialchars($_SERVER["PHP_SELF"]);
echo '">';

if (!isset($_SESSION["q31"])){
	echo '<div id="question">
<span>1. ' . $qu31 . '</span><br>
<span><input type="radio" name="q31" value="' . $qa31_1 . '">' . $qa31_1 . '</span>
<span><input type="radio" name="q31" value="' . $qa31_2 . '">' . $qa31_2 . '</span>
<span><input type="radio" name="q31" value="' . $qa31_3 . '">' . $qa31_3 . '</span>
<span><input type="radio" name="q31" value="' . $qa31_4 . '">' . $qa31_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q32"]))
{
echo '<div id="question">
<span>2. ' . $qu32 . '</span><br>
<span><input type="radio" name="q32" value="' . $qa32_1 . '">' . $qa32_1 . '</span>
<span><input type="radio" name="q32" value="' . $qa32_2 . '">' . $qa32_2 . '</span>
<span><input type="radio" name="q32" value="' . $qa32_3 . '">' . $qa32_3 . '</span>
<span><input type="radio" name="q32" value="' . $qa32_4 . '">' . $qa32_4 . '</span>
<br></div>';
}
if (!isset($_SESSION["q33"]))
{
echo '<div id="question">
<span>3. ' . $qu33 . '</span><br>
<span><input type="radio" name="q33" value="' . $qa33_1 . '">' . $qa33_1 . '</span>
<span><input type="radio" name="q33" value="' . $qa33_2 . '">' . $qa33_2 . '</span>
<span><input type="radio" name="q33" value="' . $qa33_3 . '">' . $qa33_3 . '</span>
<span><input type="radio" name="q33" value="' . $qa33_4 . '">' . $qa33_4 . '</span>
<br></div>';
}
echo '<div id="name">
Your name: <input type="text" name="name" maxlength="20" value="' . $_SESSION["name"] . '" required></div>';
echo '<br><br>
	<input class="send" id="final" type="submit" name="submit" value="Submit">';
}
else
{
	include '404.php';
}
?>
