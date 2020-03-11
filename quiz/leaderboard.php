<?php include 'header.php';?>
<?php include 'top.php';?>
<?php include 'questions.php';?>
<?php
$players = array();
$playerFile = fopen("leaderboard.json", "r");
$line == "";
while (!feof($playerFile)) {
$currC = fgetc($playerFile);
	if ($currC == chr(0x0A))
	{
		array_push($players, array(json_decode($line, true)));
		$line = "";
	}
	else
		$line = $line . $currC;
}
fclose($file);
$playersSaved = $players;


$arrInd = array(0);
$curr = 1;
while ($curr < count($players))
{
	array_push($arrInd, $curr);
	$curr++;
}
array_push($arrInd, $curr);
echo '<div id="leaderboard">
<h1 class="title">Leaderboard</h1>';

$lastInd = end($arrInd);
while (count($players) > 0)
{
	$best = reset($players)[0];
	$bestInd = reset($arrInd);
	$curr = next($players)[0];
	$currInd = next($arrInd);

	while ($currInd != $lastInd)
	{
		if ($best['points'] < $curr['points'])
		{
			$best = current($players)[0];
			$bestInd = current($arrInd);
		}
		$curr = next($players)[0];
		$currInd = next($arrInd);
	}
	echo '<span class="score"><span class="name">' . $best['name'] . '</span><span class="points">' . $best['points'] . '</span></span>';
	unset($players[$bestInd]);
	unset($arrInd[$bestInd]);}

echo '</div>';

$G1 = 0;
$G2 = 0;
$G3 = 0;
$G4 = 0;

$B1 = 0;
$B2 = 0;
$B3 = 0;
$B4 = 0;

$L1 = 0;
$L2 = 0;
$L3 = 0;
$L4 = 0;

$totalP = 0;
$aveP = 0;
$i = 0;

while ($i < count($playersSaved))
{
	if ($playersSaved[$i][0]['team'] == $qa31_1)
		$G1 += $playersSaved[$i][0]['points'];
	else if ($playersSaved[$i][0]['team'] == $qa31_2)
		$G2 += $playersSaved[$i][0]['points'];
	else if ($playersSaved[$i][0]['team'] == $qa31_3)
		$G3 += $playersSaved[$i][0]['points'];
	else if ($playersSaved[$i][0]['team'] == $qa31_4)
		$G4 += $playersSaved[$i][0]['points'];

	$totalP += $playersSaved[$i][0]['points'];

	if ($playersSaved[$i][0]['branch'] == $qa32_1)
		$B1++;
	else if ($playersSaved[$i][0]['branch'] == $qa32_2)
		$B2++;
	else if ($playersSaved[$i][0]['branch'] == $qa32_3)
		$B3++;
	else if ($playersSaved[$i][0]['branch'] == $qa32_4)
		$B4++;

	if ($playersSaved[$i][0]['place'] == $qa33_1)
		$L1++;
	else if ($playersSaved[$i][0]['place'] == $qa33_2)
		$L2++;
	else if ($playersSaved[$i][0]['place'] == $qa33_3)
		$L3++;
	else if ($playersSaved[$i][0]['place'] == $qa33_4)
		$L4++;
	$i++;
}
$aveP = $totalP / $i;


$coalitions = array();
array_push($coalitions, array("Name"=>$qa31_1, "points"=>$G1));
array_push($coalitions, array("Name"=>$qa31_2, "points"=>$G2));
array_push($coalitions, array("Name"=>$qa31_3, "points"=>$G3));
array_push($coalitions, array("Name"=>$qa31_4, "points"=>$G4));

$branches = array();
array_push($branches, array("Name"=>$qa32_1, "amount"=>$B1));
array_push($branches, array("Name"=>$qa32_2, "amount"=>$B2));
array_push($branches, array("Name"=>$qa32_3, "amount"=>$B3));
array_push($branches, array("Name"=>$qa32_4, "amount"=>$B4));

$places = array();
array_push($places, array("Name"=>$qa33_1, "amount"=>$L1));
array_push($places, array("Name"=>$qa33_2, "amount"=>$L2));
array_push($places, array("Name"=>$qa33_3, "amount"=>$L3));
array_push($places, array("Name"=>$qa33_4, "amount"=>$L4));


$arraySpot = array(0, 1, 2, 3);
$spotsCoa = $arraySpot;
$spotsBran = $arraySpot;
$spotsPla = $arraySpot;

echo '<div id="coalitions">';
echo '<h1 class="coa">Coalition leaderboard</h1>';
while (count($coalitions) > 0)
{
	$lastCoai = end($spotsCoa);
	$bestCoai = reset($spotsCoa);
	$bestCoa = reset($coalitions);
	$currCoai = $bestCoai;
	while ($currCoai != $lastCoai)
	{
		$currCoa = next($coalitions);
		$currCoai = next($spotsCoa);
		if ($bestCoa['points'] < $currCoa['points'])
		{
			$bestCoai = $currCoai;
			$bestCoa = $currCoa;
		}
	}
	echo '<span class="score"><span class="name">' . $bestCoa['Name'] . '</span><span class="points">' . $bestCoa['points'] . '</span></span>';
	unset($coalitions[$bestCoai]);
	unset($spotsCoa[$bestCoai]);
	echo '<br>';
#	echo '<br>' . count($coalitions);
}


echo '</div>';
echo '<div id="branches">';
echo '<h1 class="bran">Top branches</h1>';
while (count($branches) > 0)
{
	$lastBrani = end($spotsBran);
	$bestBrani = reset($spotsBran);
	$bestBran = reset($branches);
	$currBrani = $bestBrani;
	while ($currBrani != $lastBrani)
	{
		$currBran = next($branches);
		$currBrani = next($spotsBran);
		if ($bestBran['amount'] < $currBran['amount'])
		{
			$bestBrani = $currBrani;
			$bestBran = $currBran;
		}
	}
	echo '<span class="score"><span class="name">' . $bestBran['Name'] . '</span><span class="points">' . $bestBran['amount'] . '</span></span>';
	echo '<br>';
	unset($branches[$bestBrani]);
	unset($spotsBran[$bestBrani]);
}
echo '</div>';

echo '<div id="locations">';
echo '<h1 class="bran">Favorite locations</h1>';
while (count($places) > 0)
{
	$lastPlai = end($spotsPla);
	$bestPlai = reset($spotsPla);
	$bestPla = reset($places);
	$currPlai = $bestPlai;
	while ($currPlai != $lastPlai)
	{
		$currPla = next($places);
		$currPlai = next($spotsPla);
		if ($bestPla['amount'] < $currPla['amount'])
		{
			$bestPlai = $currPlai;
			$bestPla = $currPla;
		}
	}
	echo '<span class="score"><span class="name">' . $bestPla['Name'] . '</span><span class="points">' . $bestPla['amount'] . '</span></span>';
	echo '<br>';
	unset($places[$bestPlai]);
	unset($spotsPla[$bestPlai]);
}
echo '</div>';

#echo '<span class="score"><span class="name">' . $qa33_1 . '</span><span class="points">' . $Fora . '</span></span>';





#echo 'Fora ' . $Fora . '<br>Guard ' . $Guard . '<br>Builders ' . $Build . '<br>Bocal ' . $Bocal . '<br><br>';
#echo 'PhP ' . $PHP . '<br>Shell ' . $Shell . '<br>Algorithm ' . $Algo . '<br>Graphics ' . $Grap . '<br><br>';
#echo 'C1 ' . $C1 . '<br>C2 ' . $C2 . '<br>C3 ' . $C3 . '<br>Home ' . $Home . '<br><br>';



echo 'Total points = ' . $totalP . '<br>';
echo 'Average points = ' . $aveP;
echo '</div>';

?>

<?php include 'footer.php';?>
