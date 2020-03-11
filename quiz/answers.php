<?php include 'questions.php';?>
<?php
if (isset($_SESSION["answers"]))
{
	if (!isset($_SESSION["end"]))
	{
		echo "no end time";
		session_unset();
		header("Refresh:0; url=index.php");
	}
	$points = 0;
echo '<h1 class="answers">The Amazing Quiz</h1>
	<h2>The answers</h2>';
echo '<h3> Part 1</h3>';
echo 'Question 1: ' . $qu11 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa11_c .'</span><br>';
if ($_SESSION["q11"] != $qa11_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q11"] . '</span><br>';
else
	$points++;
echo '<br>Question 2: ' . $qu12 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa12_c . '</span><br>';
if ($_SESSION["q12"] != $qa12_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q12"] . '</span><br>';
else
	$points++;
echo '<br>Question 3: ' . $qu13 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa13_c . '</span><br>';
if ($_SESSION["q13"] != $qa13_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q13"] . '</span><br>';
else
	$points++;
echo '<br>Question 4: ' . $qu14 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa14_c . '</span><br>';
if ($_SESSION["q14"] != $qa14_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q14"] . '</span><br>';
else
	$points++;
echo '<br>Question 5: ' . $qu15 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa15_c . '</span><br>';
if ($_SESSION["q15"] != $qa15_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q15"] . '</span><br>';
else
	$points++;
echo '<br>Question 6: ' . $qu16 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa16_c . '</span><br>';
if ($_SESSION["q16"] != $qa16_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q16"] . '</span><br>';
else
	$points++;
echo '<br>Question 7: ' . $qu17 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa17_c . '</span><br>';
if ($_SESSION["q17"] != $qa17_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q17"] . '</span><br>';
else
	$points++;
echo '<br>Question 8: ' . $qu18 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa18_c . '</span><br>';
if ($_SESSION["q18"] != $qa18_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q18"] . '</span><br>';
else
	$points++;
echo '<br>Question 9: ' . $qu19 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa19_c . '</span><br>';
if ($_SESSION["q19"] != $qa19_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q19"] . '</span><br>';
else
	$points++;
echo '<br>Question 10: ' . $qu110 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa110_c . '</span><br>';
if ($_SESSION["q110"] != $qa110_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q110"] . '</span><br>';
else
	$points++;


echo '<br><br><br>';
echo '<h3> Part 2</h3>';
echo 'Question 1: ' . $qu21 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa21_c . '</span><br>';
if ($_SESSION["q21"] != $qa21_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q21"] . '</span><br>';
else
	$points++;
echo '<br>Question 2: ' . $qu22 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa22_c .'</span><br>';
if ($_SESSION["q22"] != $qa22_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q22"] . '</span><br>';
else
	$points++;
echo '<br>Question 3: ' . $qu23 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa23_c .'</span><br>';
if ($_SESSION["q23"] != $qa23_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q23"] . '</span><br>';
else
	$points++;
echo '<br>Question 4: ' . $qu24 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa24_c . '</span><br>';
if ($_SESSION["q24"] != $qa24_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q24"] . '</span><br>';
else
	$points++;
echo '<br>Question 5: ' . $qu25 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa25_c . '</span><br>';
if ($_SESSION["q25"] != html_entity_decode($qa25_c))
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q25"] . '</span><br>';
else
	$points++;
echo '<br>Question 6: ' . $qu26 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa26_c . '</span><br>';
if ($_SESSION["q26"] != $qa26_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q26"] . '</span><br>';
else
	$points++;
echo '<br>Question 7: ' . $qu27 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa27_c . '</span><br>';
if ($_SESSION["q27"] != $qa27_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q27"] . '</span><br>';
else
	$points++;
echo '<br>Question 8: ' . $qu28 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa28_c . '</span><br>';
if ($_SESSION["q28"] != $qa28_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q28"] . '</span><br>';
else
	$points++;
echo '<br>Question 9: ' . $qu29 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa29_c . '</span><br>';
if ($_SESSION["q29"] != $qa29_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q29"] . '</span><br>';
else
	$points++;
echo '<br>Question 10: ' . $qu210 . '<br>';
echo '<span class="correct">The correct answer: ' . $qa210_c . '</span><br>';
if ($_SESSION["q210"] != $qa210_c)
	echo '<span class="wrong"> Your answer: ' . $_SESSION["q210"] . '</span><br>';
else
	$points++;

$timeTaken = $_SESSION["end"] - $_SESSION["start"];
if ($timeTaken == 0)
	$timeTaken = 300 * 4.2;
else
	$timeTaken = 300 / $timeTaken * 4.2;
$correct = $points;
$points = floor($points * $timeTaken);
echo '<span class="finalScore">You scored ' . $points . ' point';
if ($points != 0)
	echo 's';
echo '! Check out the <a href="leaderboard.php" title="Leaderboard">leaderboard</a> to see how well you did</span>';
	if (!isset($_SESSION["submit"]))
	{
		$submitDay = date("Y-m-d", $_SESSION["end"]);
		$timeTaken = $_SESSION["end"] - $_SESSION["start"];
		$addr = filter_var($_SERVER['REMOTE_ADDR'], FILTER_VALIDATE_IP);
		$answer = array("name"=>$_SESSION["name"], "team"=>$_SESSION["q31"], "branch"=>$_SESSION["q32"], "place"=>$_SESSION["q33"], "points"=>$points, "correct"=>$correct, "time"=>$timeTaken, "submitted"=>$submitDay, "address"=>$addr);
		$json = fopen("leaderboard.json", "a");
		fwrite($json, json_encode($answer));
		fwrite($json, "\n");
	fclose($json);
	$_SESSION["submit"] = "true";
	}
}
else
{
	include '404.php';
}
?>
