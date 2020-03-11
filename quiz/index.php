<?php session_start(['cookie_lifetime' => 86400, ]);
#ini_set('display_errors', 1);
#ini_set('display_startup_errors', 1);
#error_reporting(E_ALL);
?>
<?php include 'header.php';
include 'top.php'; ?>
<?php include 'questions.php';?>
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if (isset($_POST["GO"]))
		$_SESSION["start"] = time();
	// PART 1
	if (isset($_POST["q11"]))
		$_SESSION["q11"] = $_POST["q11"];
	if (isset($_POST["q12"]))
		$_SESSION["q12"] = $_POST["q12"];
	if (isset($_POST["q13"]))
		$_SESSION["q13"] = $_POST["q13"];
	if (isset($_POST["q14"]))
		$_SESSION["q14"] = $_POST["q14"];
	if (isset($_POST["q15"]))
		$_SESSION["q15"] = $_POST["q15"];
	if (isset($_POST["q16"]))
		$_SESSION["q16"] = $_POST["q16"];
	if (isset($_POST["q17"]))
		$_SESSION["q17"] = $_POST["q17"];
	if (isset($_POST["q18"]))
		$_SESSION["q18"] = $_POST["q18"];
	if (isset($_POST["q19"]))
		$_SESSION["q19"] = $_POST["q19"];
	if (isset($_POST["q110"]))
		$_SESSION["q110"] = $_POST["q110"];
	// PART 2
	if (isset($_POST["q21"]))
		$_SESSION["q21"] = $_POST["q21"];
	if (isset($_POST["q22"]))
		$_SESSION["q22"] = $_POST["q22"];
	if (isset($_POST["q23"]))
		$_SESSION["q23"] = $_POST["q23"];
	if (isset($_POST["q24"]))
		$_SESSION["q24"] = $_POST["q24"];
	if (isset($_POST["q25"]))
		$_SESSION["q25"] = $_POST["q25"];
	if (isset($_POST["q26"]))
		$_SESSION["q26"] = $_POST["q26"];
	if (isset($_POST["q27"]))
		$_SESSION["q27"] = $_POST["q27"];
	if (isset($_POST["q28"]))
		$_SESSION["q28"] = $_POST["q28"];
	if (isset($_POST["q29"]))
		$_SESSION["q29"] = $_POST["q29"];
	if (isset($_POST["q210"]))
		$_SESSION["q210"] = $_POST["q210"];
	// PART 3
	if (isset($_POST["q31"]))
		$_SESSION["q31"] = $_POST["q31"];
	if (isset($_POST["q32"]))
		$_SESSION["q32"] = $_POST["q32"];
	if (isset($_POST["q33"]))
		$_SESSION["q33"] = $_POST["q33"];
	if (isset($_POST["name"]))
		$_SESSION["name"] = htmlspecialchars($_POST["name"]);
}
#echo session_id();
#echo '<br>';
#echo session_save_path();
#echo "<br>";
#echo var_dump($_SESSION);
?>

<?php
if (!isset($_SESSION["start"]))
{
	echo 'Click on the button to start the quiz. You will get scored based on correct answers and time spent.<br>';
	echo 'There are 20 timed questions and a couple statistical questions that are not timed<br><br>';
	echo '<form method="post" action"' . htmlspecialchars($_SERVER["PHP_SELF"]) . '">';
	echo '<input class="send" name="GO" type="submit" value="Start">';
	echo '</form>';
}
else if (!isset($_SESSION["q11"]) || !isset($_SESSION["q12"]) || !isset($_SESSION["q13"]) || !isset($_SESSION["q14"]) || !isset($_SESSION["q15"]) || !isset($_SESSION["q16"]) || !isset($_SESSION["q17"]) || !isset($_SESSION["q18"]) || !isset($_SESSION["q19"]) || !isset($_SESSION["q110"]))
{
	$_SESSION["get1"] = "Helloo world";
	include 'q1.php';
	unset($_SESSION["get1"]);
}
else if (!isset($_SESSION["q21"]) || !isset($_SESSION["q22"]) || !isset($_SESSION["q23"]) || !isset($_SESSION["q24"]) || !isset($_SESSION["q25"]) || !isset($_SESSION["q26"]) || !isset($_SESSION["q27"]) || !isset($_SESSION["q28"]) || !isset($_SESSION["q29"]) || !isset($_SESSION["q210"]))
{
	$_SESSION["get2"] = "true";
	include 'q2.php';
	unset($_SESSION["get2"]);
}
else if (!isset($_SESSION["q31"]) || !isset($_SESSION["q32"]) || !isset($_SESSION["q33"]))
{
	$_SESSION["get3"] = "true";
	include 'q3.php';
	unset($_SESSION["get3"]);
}
else
{
	$_SESSION["answers"] = "true";
	include 'answers.php';
	unset($_SESSION["answers"]);
}
?>

</form>
</div>
<?php include 'footer.php'; ?>
